#include <vector>
#include <iostream>

#include "commune.h"
#include "matflux.h"
#include "lien.h"

void lien::calcul_max(int numdc, float lien, int dcmaxlien) 
{
    // teste valeur du lien max et le max pour maj éventuelle
    // pour la commune numdc
    if (lien > vcom[numdc].maxlien) {
        vcom[numdc].maxlien = lien ;
        vcom[numdc].dcmaxlien = dcmaxlien ;
    }
}

void lien::calcul_init()
{
    for (unsigned int i=1; i<vcom.size(); i++) {
        calcul_sim(i) ;
    }
}

void
lien::raz_calc(int numdc)
{
    for (element* p = mflux.tete_l[numdc]; p!=0; p=p->next) {
        mflux.tabval[p->numval].calc = 0 ;
    }
    for (element* p = mflux.tete_c[numdc]; p!=0; p=p->next) {
        mflux.tabval[p->numval].calc = 0 ;
    }
}

void
lien::calcul_sim(int numdc)
{
    std::cout << numdc << std::endl ;
    // on parcoure simultanément la ligne et la colonne numdc
    // pl pointeur sur ligne
    element *pl = mflux.tete_l[numdc] ;
    // pc pointeur sur colonne
    element *pc = mflux.tete_c[numdc] ;
    // on parcoure tant que les 2 pointeurs ne sont pas nuls
    while (pl != 0 || pc != 0) {
        // si colonne finie ou à une valeur strictement inférieure
        // le traitement se fait qu'avec pl
        if ((pl != 0) && (pc == 0 || pl->numlc > pc->numlc)) {
            int numdc_l=numdc ;
            int numdc_c=pl->numlc ;
            if (numdc_l != numdc_c && numdc_l && numdc_c) {
                int numval=pl->numval ;
                if ( mflux.tabval[numval].calc == 0 ) {
                    float lien = calcul_elem(numdc_l, numdc_c, mflux.tabval[numval].nb, 0) ;
                    mflux.tabval[numval].lien = lien ;
                    mflux.tabval[numval].calc = 1 ;
                    calcul_max(numdc_l,lien, numdc_c) ;
                }
            }
           pl = pl->next;
        // si ligne finie ou à une valeur strictement inférieure
        // le traitement ne se fait qu'avec pc
        } else if ((pc != 0) && (pl == 0 ||pc->numlc > pl->numlc)) {
            int numdc_l=pc->numlc ;
            int numdc_c=numdc ;
            if (numdc_l != numdc_c && numdc_l && numdc_c) {
                int numval=pc->numval ;
                if ( mflux.tabval[numval].calc == 0 ) {
                    float lien = calcul_elem(numdc_l, numdc_c, 0,mflux.tabval[numval].nb) ;
                    mflux.tabval[numval].lien = lien ;
                    mflux.tabval[numval].calc = 1 ;
                    calcul_max(numdc_l,lien, numdc_c) ;
                }
            }
            pc = pc->next;
        } else {
            int numdc_l=numdc ;
            int numdc_c=pl->numlc ;
            if (numdc_l != numdc_c && numdc_l && numdc_c) {
                int numval=pl->numval ;
                int numval_d=pc->numval ;
                float lien = 0 ;
                if ( mflux.tabval[numval].calc == 0 ) {
                    lien = calcul_elem(numdc_l, numdc_c, 
                                 mflux.tabval[numval].nb, mflux.tabval[numval_d].nb) ;
                    mflux.tabval[numval].lien = lien ;
                    mflux.tabval[numval].calc = 1 ;
                    calcul_max(numdc_l,lien, numdc_c) ;
                }
                if ( mflux.tabval[numval_d].calc == 0 ) {
                    if (! is_sym()) {
                        lien = calcul_elem(numdc_c, numdc_l, 
                        mflux.tabval[numval_d].nb, mflux.tabval[numval].nb) ;
                    }
                    mflux.tabval[numval_d].lien = lien ;
                    mflux.tabval[numval_d].calc = 1 ;
                    calcul_max(numdc_c,lien, numdc_l) ;
                }
            }
            pl = pl->next;
            pc = pc->next;
        }
    }
}
