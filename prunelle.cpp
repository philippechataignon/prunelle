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
    std::cerr << "Prunelle - (c) Philippe CHATAIGNON" << "\n" << 
    rev.substr(1,rev.length()-1) << " - " << __DATE__ << " - " << __TIME__ << std::endl;

    options opt(argc,argv) ;


    int nbcom, nbflux ;
    std::cin >> nbflux ;
    std::cin >> nbcom ;
    std::cerr << nbflux << "/" << nbcom << "/" << opt.get_typelien() << "/" << opt.get_verbeux() <<std::endl ;

    std::vector<commune> vcom ;
    vcom.reserve(nbcom) ;
    matflux mflux (nbcom,nbflux);
    lecture_fich (std::cin, mflux, vcom);

    lien* vlien ;
    switch (opt.get_typelien()) {
        case 1 : vlien=new lien_aa(mflux,vcom) ; break;
        case 2 : vlien=new lien_es(mflux,vcom) ; break;
        case 3 : vlien=new lien_sta(mflux,vcom) ; break;
        case 4 : vlien=new lien_phc(mflux,vcom) ; break;
        default : vlien=new lien_aa(mflux,vcom) ; break;
    }

    std::cerr << "Calcul des liens init" << std::endl ;
    vlien->calcul_init() ;

    bool fin = false ;
    int cpt = 0;
    double prev_maxlien =  vlien->val_init() ;

    std::ifstream pre (opt.get_pre().c_str());
    std::ofstream out (opt.get_out().c_str());
    if (opt.get_out() != "" ) {
        std::cerr << "Début préagrégation" << std::endl ;

        while (!pre.eof()) {
            int sat, pole ;
            pre >> pole >> sat ;
            out << vcom[pole].nom << " < " <<vcom[sat].nom << '\t' << 0 << "\t" << 0 << "\t" << vcom[sat] << "\t";
            if (opt.get_verbeux()  >= 1) {
                std::cerr << "PRE: " << vcom[pole].nom << "<" <<vcom[sat].nom << "\n" ; 
            }
            agrege(mflux,vcom,pole,sat) ;
            vlien->raz_calc(pole) ;
            vlien->calcul_sim(pole) ;
            out << vcom[pole] << "\n" ; 
        }
    }

    std::cerr << "Début boucle principale" << std::endl ;
    while (!fin && cpt++<(nbcom-1)) {
        // mflux.affiche_mat() ;
        if ((cpt % 1000) == 0) {
            std::cerr << "Itération n°" << cpt << std::endl ;
        }
        double maxlien = vlien->val_init() ;
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
            double rebond = 0 ;
            if (maxlien > prev_maxlien && cpt != 1) {
                rebond = maxlien - prev_maxlien ;
            } else {
                rebond = 0 ;
            }
            // out << pole << '\t' << sat << '\t' << maxlien << "\t" << rebond << "\n" ; 
            out << vcom[pole].nom << " < " <<vcom[sat].nom << '\t' << maxlien << "\t" << rebond << "\t" << vcom[sat] << "\t";
            if (opt.get_verbeux()  >= 1) {
                std::cerr << "AGR: " << vcom[pole].nom << "<" <<vcom[sat].nom << '\t' << maxlien << "\t" << rebond << "\n" ; 
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
