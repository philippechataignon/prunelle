#include <fstream>
#include <iostream>
#include <vector>

#include "globals.h"
#include "lien.h"
#include "liens.h"
#include "commune.h"
#include "matflux.h"
#include "parse_opt.h"

int main(int argc, char* argv[])
{
    std::cout << "Prunelle V 8.01 - " << __DATE__ << " - " << __TIME__ <<
        std::endl;

    char f_in[128] ;
    char f_out[128] ;
    int  verbeux = 1;
    int  f_lien = 0 ;

    parse_opt(argc,argv,&verbeux,f_in,f_out,&f_lien) ;

    if (! *f_in) {
        std::cout << "Erreur : pas de fichier indiqué en entrée (-i nom_fichier)" << std::endl ;
        ::help() ;
        std::exit(1);
    }

    std::ifstream in (f_in);
    if (in == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier prunelle" << std::endl ;
        std::exit(1);
    }

    std::ofstream out (f_out);
    if (out == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
        std::exit(1);
    }

    const int type = f_lien ;

    int nbcom, nbflux ;
    in >> nbflux ;
    in >> nbcom ;
    std::cout << nbflux << "/" << nbcom << "/" << type <<std::endl ;

    std::vector<commune> vcom ;
    vcom.reserve(nbcom) ;
    matflux mflux (nbcom,nbflux);
    lecture_fich (in, mflux, vcom);

    lien* vlien ;

    if (type == 0) {
        vlien=new lien_aa(mflux,vcom) ;
    } else if (type == 1) {
        vlien=new lien_es(mflux,vcom) ;
    }
    
    std::cout << "Calcul des liens init" << std::endl ;
    vlien->calcul_init() ;
    bool fin = false ;
    int cpt = 0;

    std::cout << "Début boucle principale" << std::endl ;
    while (!fin && cpt++<(nbcom-1)) {
        if ((cpt % 1000) == 0) {
            std::cout << "Itération n°" << cpt << std::endl ;
        }
        float maxlien = vlien->val_init() ;
        int sat = -1 ;
        int pole = -1 ;
        for(int i=0 ; i<nbcom; i++) {
            if (vcom[i].status && 
                    (vcom[i].maxlien > maxlien || 
                        (sat != -1 && vcom[i].maxlien==maxlien && vcom[i].act < vcom[sat].act)
                    )
               ) {
                sat = i ;
                pole = vcom[i].dcmaxlien ;
                maxlien = vcom[i].maxlien ;
            }
        }
        fin = (sat == -1 || pole == -1 || maxlien<=vlien->val_stop() ) ;
        if (!fin) {
            out << vcom[pole].nom << " < " <<vcom[sat].nom << '\t' << maxlien << "\t" << vcom[sat] << "\t" ; 
            if (verbeux >= 1) {
                std::cout << "AGR: " << vcom[pole].nom << "<" <<vcom[sat].nom << '\t' << maxlien << "\n" ; 
            }
            agrege(mflux,vcom,pole,sat) ;
            vlien->calcul_sim (pole) ;
            out << vcom[pole] << "\n" ; 
        }
    }
    return 0;
}
