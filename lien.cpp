#include <vector>

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
