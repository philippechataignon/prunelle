#include <fstream>
#include <iostream>
#include <vector>

#include "lien.h"
#include "liens.h"
#include "commune.h"
#include "matflux.h"
#include "options.h"
#include "utils.h"
#include "globals.h"

int main(int argc, char* argv[])
{
    std::cout << "Prunelle V 8.01 - " << __DATE__ << " - " << __TIME__ <<
        std::endl;

    options opt(argc,argv) ;
    std::cout << opt.get_in() << std::endl ;

    if (opt.get_in().empty()) {
        std::cout << "Erreur : pas de fichier indiqué en entrée (-i nom_fichier)" << std::endl ;
        opt.help() ;
        std::exit(1);
    }

    std::ifstream in (opt.get_in().c_str());
    if (in == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier prunelle" << std::endl ;
        std::exit(1);
    }

    std::ofstream out (opt.get_out().c_str());
    if (out == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
        std::exit(1);
    }

    int nbcom, nbflux ;
    in >> nbflux ;
    in >> nbcom ;
    std::cout << nbflux << "/" << nbcom << "/" << opt.get_typelien() << "/" << opt.get_verbeux() <<std::endl ;

    std::vector<commune> vcom ;
    vcom.reserve(nbcom) ;
    matflux mflux (nbcom,nbflux);
    lecture_fich (in, mflux, vcom);

    lien* vlien ;
    switch (opt.get_typelien()) {
        case 1 : vlien=new lien_aa(mflux,vcom) ; break;
        case 2 : vlien=new lien_es(mflux,vcom) ; break;
        case 3 : vlien=new lien_sta(mflux,vcom) ; break;
        default : vlien=new lien_aa(mflux,vcom) ; break;
    }

    std::cout << "Calcul des liens init" << std::endl ;
    vlien->calcul_init() ;

    bool fin = false ;
    int cpt = 0;
    float prev_maxlien =  vlien->val_init() ;

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
            float rebond = 0 ;
            if (maxlien > prev_maxlien && cpt != 1) {
                rebond = maxlien - prev_maxlien ;
            } else {
                rebond = 0 ;
            }
            out << vcom[pole].nom << " < " <<vcom[sat].nom << '\t' << maxlien << "\t" << rebond << "\t" << vcom[sat] << "\t" ; 
            if (opt.get_verbeux()  >= 1) {
                std::cout << "AGR: " << vcom[pole].nom << "<" <<vcom[sat].nom << '\t' << maxlien << "\t" << rebond << "\n" ; 
            }
            agrege(mflux,vcom,pole,sat) ;
            vlien->calcul_sim (pole) ;
            out << vcom[pole] << "\n" ; 
        }
        prev_maxlien = maxlien ;
    }
    return 0;
}
