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

// $Id: prunelle.cpp 53 2005-08-10 09:24:28Z philippe $


int main(int argc, char* argv[])
{
    std::string rev = "$Revision" ;
    std::cout << "Prunelle - (c) 2005 Philippe CHATAIGNON" << "\n" << 
    rev.substr(1,rev.length()-1) << " - " << __DATE__ << " - " << __TIME__ << std::endl;

    options opt(argc,argv) ;
    std::cout << opt.get_in() << std::endl ;

    std::ofstream out (opt.get_out().c_str());
    if (out == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
        std::exit(1);
    }

    int nbcom, nbflux ;
    std::cin >> nbflux ;
    std::cin >> nbcom ;
    std::cout << nbflux << "/" << nbcom << "/" << opt.get_typelien() << "/" << opt.get_verbeux() <<std::endl ;

    std::vector<commune> vcom ;
    vcom.reserve(nbcom) ;
    matflux mflux (nbcom,nbflux);
    lecture_fich (std::cin, mflux, vcom);

    for (int i=0; i<vcom.size(); i++) {
        out << vcom[i] << "\n" ;
    }

    lien* vlien ;
    switch (opt.get_typelien()) {
        case 1 : vlien=new lien_aa(mflux,vcom) ; break;
        case 2 : vlien=new lien_es(mflux,vcom) ; break;
        case 3 : vlien=new lien_sta(mflux,vcom) ; break;
        case 4 : vlien=new lien_phc(mflux,vcom) ; break;
        default : vlien=new lien_aa(mflux,vcom) ; break;
    }

    std::cout << "Calcul des liens init" << std::endl ;
    vlien->calcul_init() ;

    bool fin = false ;
    int cpt = 0;
    float prev_maxlien =  vlien->val_init() ;

    std::cout << "Début boucle principale" << std::endl ;
    while (!fin && cpt++<(nbcom-1)) {
        // mflux.affiche_mat() ;
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
        fin = (sat == -1 || pole == -1 || maxlien<=vlien->val_stop() || maxlien<opt.get_valmax() ) ;
        if (!fin) {
            float rebond = 0 ;
            if (maxlien > prev_maxlien && cpt != 1) {
                rebond = maxlien - prev_maxlien ;
            } else {
                rebond = 0 ;
            }
            // out << pole << '\t' << sat << '\t' << maxlien << "\t" << rebond << "\n" ; 
            out << vcom[pole].nom << " < " <<vcom[sat].nom << '\t' << maxlien << "\t" << rebond << "\t" << vcom[sat] << "\t";
            if (opt.get_verbeux()  >= 1) {
                std::cout << "AGR: " << vcom[pole].nom << "<" <<vcom[sat].nom << '\t' << maxlien << "\t" << rebond << "\n" ; 
            }
            agrege(mflux,vcom,pole,sat) ;
            vlien->raz_calc(pole) ;
            vlien->calcul_sim(pole) ;
            out << vcom[pole] << "\n" ; 
        }
        prev_maxlien = maxlien ;
    }
    return 0;
}
