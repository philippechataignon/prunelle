#include <fstream>
#include <vector>

#include "globals.h"
#include "lien.h"
#include "commune.h"
#include "matflux.h"

int main(int argc, char* argv[])
{
    std::cout << "Prunelle V 8.01 - " << __DATE__ << " - " << __TIME__ <<
        std::endl;

    if (argc != 3 ) {
        std::cout << "Entrer fichier prunelle\n";
        std::exit (0);
    }

    std::ifstream in (argv[1]);
    if (in == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier prunelle" << std::endl ;
        exit(1);
    }

    std::ofstream out (argv[2]);
    if (out == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
        exit(1);
    }

    int type = 0;

    int nbcom, nbflux ;
    in >> nbflux ;
    in >> nbcom ;
    std::cout << nbflux << "/" << nbcom << std::endl ;

    std::vector<commune> vcom ;
    vcom.reserve(nbcom) ;
    matflux mflux (nbcom,nbflux);
    lecture_fich (in, mflux, vcom);
    calcul_lien_init(mflux,vcom,type) ;
    bool fin = false ;
    int cpt = 0;

    while (!fin && cpt++<(nbcom-1)) {
        //mflux.imprime() ;
        float maxlien = -100.0 ;
        int dca = -1 ;
        int dcb = -1 ;
        for(int i=0 ; i<nbcom; i++) {
            if (vcom[i].status && 
                    (vcom[i].maxlien > maxlien || 
                        (dca != -1 && vcom[i].maxlien>= maxlien - 1e-3 && vcom[i].act > vcom[dca].act)
                    )
                ) {
                dca = i ;
                dcb = vcom[i].dcmaxlien ;
                maxlien = vcom[i].maxlien ;
            }
        }
        fin = (dca == -1 || dcb == -1 || maxlien < 1E-40) ;
        if (!fin) {
            std::cout << "AGREG : " << vcom[dca].nom << "\t" <<vcom[dcb].nom << '\t' << maxlien << std::endl ; 
            out << vcom[dca].nom << "\t" <<vcom[dcb].nom << '\t' << maxlien << std::endl ; 
            std::cout << vcom[dca] << "\n" <<vcom[dcb] << '\n' ; 
            agrege(mflux,vcom,dcb,dca) ;
            std::cout << vcom[dca] << std::endl ; 
        }
    }
    return 0;
}
