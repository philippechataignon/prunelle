#include <fstream>
#include <vector>

#include "globals.h"
#include "commune.h"
#include "matflux.h"

int main(int argc, char* argv[])
{
    std::cout << "Prunelle V 8.01 - " << __DATE__ << " - " << __TIME__ <<
        std::endl;

    if (argc != 2 ) {
        std::cout << "Entrer fichier prunelle\n";
        std::exit (0);
    }

    std::ifstream in (argv[1]);
    if (in == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier prunelle" << std::endl ;
        exit(1);
    }

    // std::ofstream out (argv[2]);
    // if (out == 0) {
    //     std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
    //     exit(1);
    // }

    int nbcom, nbflux ;
    in >> nbflux ;
    in >> nbcom ;
    std::cout << nbflux << "/" << nbcom << std::endl ;

    std::vector<commune> vcom ;
    vcom.reserve(nbcom) ;
    matflux mflux (nbcom,nbflux);
    lecture_fich (in, mflux, vcom);
    calcul_lien_init(mflux,vcom) ;

    while (1) {
        float maxlien = -100.0 ;
        int   dca = -1 ;
        int dcb = -1 ;
        for(int i=0 ; i<nbcom; i++) {
            if (vcom[i].status && vcom[i].maxlien > maxlien) {
                maxlien = vcom[i].maxlien ;
                dca = i ;
                dcb = vcom[i].dcmaxlien ;
            }
        }
        std::cout << dca << "(" << vcom[dca].nom << ")"  << "\t" << dcb << "(" <<vcom[dcb].nom << ")" << '\t' << maxlien << std::endl ; 
        agrege(mflux,vcom,dca,dcb) ;
        calcul_lien_maj(mflux,vcom) ;
    }
}
