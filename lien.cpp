#include <vector>
#include <iostream>

#include "commune.h"
#include "matflux.h"
#include "lien.h"
#include "lien_elem.h"

void calcul_lien_init(matflux & mflux, std::vector<commune> & vcom, int type)
{
    for (unsigned int i=0; i<vcom.size(); i++) {
        calcul_lien_sim(mflux, vcom, i, type) ;
    }
}

void
calcul_lien_sim(matflux & mflux, std::vector<commune> & vcom, int numdc, int type )
{
    element *pl = mflux.tete_l[numdc] ;
    element *pc = mflux.tete_c[numdc] ;
    while (pl != 0 || pc != 0) {
        if ((pl != 0) && (pc == 0 || pl->numlc > pc->numlc)) {
            int numdc_l=numdc ;
            int numdc_c=pl->numlc ;
            if (numdc_l != numdc_c && numdc_l && numdc_c) {
                int numval=pl->numval ;
                float lien = calcul_lien_elem(mflux, vcom, numdc_l, numdc_c, mflux.tabval[numval].nb, 0, type) ;
                mflux.tabval[numval].lien = lien ;
                calcul_max(vcom, numdc_l,lien, numdc_c) ;
            }
            pl = pl->next;
        } else if ((pc != 0) && (pl == 0 ||pc->numlc > pl->numlc)) {
            int numdc_l=pc->numlc ;
            int numdc_c=numdc ;
            if (numdc_l != numdc_c && numdc_l && numdc_c) {
                int numval=pc->numval ;
                float lien = calcul_lien_elem(mflux, vcom, numdc_l, numdc_c, 0,mflux.tabval[numval].nb, type) ;
                mflux.tabval[numval].lien = lien ;
                calcul_max(vcom, numdc_l,lien, numdc_c) ;
            }
            pc = pc->next;
        } else {
            int numdc_l=numdc ;
            int numdc_c=pl->numlc ;
            if (numdc_l != numdc_c && numdc_l && numdc_c) {
                int numval=pl->numval ;
                int numval_d=pc->numval ;
                float lien = calcul_lien_elem(mflux, vcom, numdc_l, numdc_c, 
                             mflux.tabval[numval].nb, mflux.tabval[numval_d].nb, type) ;
                mflux.tabval[numval].lien = lien ;
                calcul_max(vcom, numdc_l,lien, numdc_c) ;
                lien = calcul_lien_elem(mflux, vcom, numdc_c, numdc_l, 
                             mflux.tabval[numval_d].nb, mflux.tabval[numval].nb, type) ;
                mflux.tabval[numval_d].lien = lien ;
                calcul_max(vcom, numdc_c,lien, numdc_l) ;
            }
            pl = pl->next;
            pc = pc->next;
        }
    }
}

void calcul_max(std::vector<commune> & vcom, int numdc, float lien, int dcmaxlien) 
{
    if (lien > vcom[numdc].maxlien) {
        vcom[numdc].maxlien = lien ;
        vcom[numdc].dcmaxlien = dcmaxlien ;
    }
}
