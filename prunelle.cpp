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

    if (argc != 4 ) {
        std::cout << "Entrer fichier prunelle\n";
        std::exit (0);
    }

    std::ifstream in (argv[1]);
    if (in == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier prunelle" << std::endl ;
        std::exit(1);
    }

    std::ofstream out (argv[2]);
    if (out == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
        std::exit(1);
    }

    const int type = std::atoi(argv[3]) ;

    int nbcom, nbflux ;
    in >> nbflux ;
    in >> nbcom ;
    std::cout << nbflux << "/" << nbcom << "/" << type <<std::endl ;

    std::vector<commune> vcom ;
    vcom.reserve(nbcom) ;
    matflux mflux (nbcom,nbflux);
    lecture_fich (in, mflux, vcom);
    calcul_lien_init(mflux,vcom,type) ;
    bool fin = false ;
    int cpt = 0;

    while (!fin && cpt++<(nbcom-1)) {
        //mflux.affiche() ;
        float maxlien = -100.0 ;
        int sat = -1 ;
        int pole = -1 ;
        for(int i=0 ; i<nbcom; i++) {
            if (vcom[i].status && 
                    (vcom[i].maxlien > maxlien || 
                     (sat != -1 && vcom[i].maxlien>= maxlien - 1e-3 && vcom[i].act > vcom[sat].act)
                    )
               ) {
                sat = i ;
                pole = vcom[i].dcmaxlien ;
                maxlien = vcom[i].maxlien ;
            }
        }
        fin = (sat == -1 || pole == -1 || maxlien < 1E-40) ;
        if (!fin) {
            out << vcom[sat].nom << "\t" <<vcom[pole].nom << '\t' << maxlien << "\t"; 
            std::cout << "AGREG : " << vcom[pole].nom << "<" <<vcom[sat].nom << '\t' << maxlien << std::endl ; 

            agrege(mflux,vcom,pole,sat) ;
            calcul_lien(mflux, vcom, pole, type) ;
            calcul_lien_dual(mflux, vcom, pole, type) ;
            out << vcom[pole] << "\n" ; 
        }
    }
    return 0;
}
