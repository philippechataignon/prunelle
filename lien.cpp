#include <vector>
#include <iostream>

#include "commune.h"
#include "matflux.h"
#include "lien.h"
#include "lien_elem.h"

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int type)
{
    float maxlien = -1e10 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_l[numdc_l]; p != 0; p = p->next) {
        int numdc_c=p->numlc ;
        if (numdc_l != numdc_c && numdc_l && numdc_c) {
            int numval=p->numval ;
            float lien = calcul_lien_elem(mflux, vcom, numdc_l, numdc_c, mflux.tabval[numval].nb, type) ;
            mflux.tabval[numval].lien = lien ;
            if (lien > maxlien) {
                maxlien = lien ;
                dcmaxlien = numdc_c ;
            }
        }
    }
    vcom[numdc_l].maxlien = maxlien ;
    vcom[numdc_l].dcmaxlien = dcmaxlien ;
    // vcom[numdc_l].status = 1 ;
}

void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdc_c, int type) {
    element* p ;
    for (p = mflux.tete_c[numdc_c]; p != 0; p = p->next) {
        int numdc_l=p->numlc ;
        if (numdc_l != numdc_c && numdc_l && numdc_c) {
            int numval=p->numval ;
            float lien = calcul_lien_elem(mflux, vcom, numdc_l, numdc_c, mflux.tabval[numval].nb, type) ;
            mflux.tabval[numval].lien = lien ;
            if (lien > vcom[numdc_l].maxlien) {
                vcom[numdc_l].maxlien = lien ;
                vcom[numdc_l].dcmaxlien = numdc_c ;
            }
        }
    }
}

void calcul_lien_init(matflux & mflux, std::vector<commune> & vcom, int type)
{
    for (unsigned int i=0; i<vcom.size(); i++) {
        calcul_lien(mflux, vcom, i, type) ;
    }
}

void
calcul_lien_sim(matflux & mflux, std::vector<commune> & vcom, int numdc, int type )
{
//    element *pl = mflux.tete_l[numdc] ;
//    element *pc = mflux.tete_c[numdc] ;
//    // tant que les deux listes ne sont pas épuisées
//    while (pl != 0 || pc != 0) {
//        // std::cout << p << "/" << pa << "/" << pb << "/" << pa->numlc <<  "," << pb->numlc << std::endl ;
//        if ((pl != 0) && (pc == 0 || pl->numlc > pc->numlc)) {
//            #ifdef DEBUG
//                std::cout << "A" << std::endl ;
//            #endif
//            int numdc_l=numdc ;
//            int numdc_c=pl->numlc ;
//            if (numdc_l != numdc_c && numdc_l && numdc_c) {
//                int numval=p->numval ;
//                float lien = calcul_lien_elem(mflux, vcom, numdc_l, numdc_c, mflux.tabval[numval].nb, type) ;
//                mflux.tabval[numval].lien = lien ;
//                if (lien > maxlien) {
//                    maxlien = lien ;
//                    dcmaxlien = numdc_c ;
//                }
//            }
//            
//            // on prend dans la liste A : cas le plus simple
//            pl = pl->next;
//        } else if ((pc != 0) && (pl == 0 ||pc->numlc > pl->numlc)) {
//            #ifdef DEBUG
//                std::cout << "B" << std::endl ;
//            #endif
//            // on prend dans la liste B : il faut faire le changement d'indice dans le dual
//            pc = pc->next;
//        } else {
//            // on cumule les elements venant de B avec celui de A : on supprime dans le dual
//            // pour éviter les 0 inutiles
//            #ifdef DEBUG
//                std::cout << "AB" << std::endl ;
//            #endif
//            pl = pl->next;
//            pc = pc->next;
//        }
//    }
}
