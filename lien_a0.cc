#include <vector>

#include "commune.h"
#include "matflux.h"
#include "lien.h"

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdca)
{
    int a0 = vcom[numdca].act ;
    float maxlien = -1.0 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_l[numdca]; p != 0; p = p->next) {
        int numdcb=p->numlc ;
        if (numdca != numdcb && numdca && numdcb && a0) {
            int numval=p->numval ;
            float lien = static_cast<float> (100*mflux.tabval[numval].nb)/a0 ;
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

void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdcb)
{
    float maxlien = -1.0 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_c[numdcb]; p != 0; p = p->next) {
        int numdca=p->numlc ;
        int a0 = vcom[numdca].act ;
        if (numdca != numdcb && numdca && numdcb && a0) {
            int numval=p->numval ;
            float lien = static_cast<float> (100*mflux.tabval[numval].nb)/a0 ;
            mflux.tabval[numval].lien = lien ;
        }
    }
} 
