#include <vector>

#include "commune.h"
#include "matflux.h"
#include "lien.h"

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdca)
{
    int a0 = vcom[numdca].act ;
    int s0 = vcom[numdca].sta ;
    float maxlien = -1.0 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_l[numdca]; p != 0; p = p->next) {
        int numdcb=p->numlc ;
        if (numdca != numdcb && numdca && numdcb && a0) {
            int numval=p->numval ;
            int a1 = vcom[numdcb].act ;
            int s1 = vcom[numdcb].sta ;
            int sab = s0 + s1 + mflux.tabval[numval].nb + mflux.get_val(numdcb,numdca) ;

            float lien = static_cast<float> (100*sab) / (a0+a1) - static_cast<float>(100*s0)/a0 ;
            mflux.tabval[numval].lien = lien ;
            if (lien > maxlien) {
                maxlien = lien ;
                dcmaxlien = numdcb ;
            }
        }
    }
    vcom[numdca].maxlien = maxlien ;
    vcom[numdca].dcmaxlien = dcmaxlien ;
    vcom[numdca].status = 1 ;
} 

void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdca)
{
    int a0 = vcom[numdca].act ;
    int s0 = vcom[numdca].sta ;
    float maxlien = -1.0 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_c[numdca]; p != 0; p = p->next) {
        int numdcb=p->numlc ;
        if (numdca != numdcb && numdca && numdcb && a0) {
            int numval=p->numval ;
            int a1 = vcom[numdcb].act ;
            int s1 = vcom[numdcb].sta ;
            int sab = s0 + s1 + mflux.tabval[numval].nb + mflux.get_val(numdcb,numdca) ;
            float lien = static_cast<float> (100*sab) / (a0+a1) - static_cast<float>(100*s1)/a1 ;
            mflux.tabval[numval].lien = lien ;
        }
    }
} 
