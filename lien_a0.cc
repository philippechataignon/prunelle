#include <vector>

#include "commune.h"
#include "matflux.h"
#include "lien.h"

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdc_l)
{
    int a0 = vcom[numdc_l].act ;
    float maxlien = -1.0 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_l[numdc_l]; p != 0; p = p->next) {
        int numdc_c=p->numlc ;
            // std::cout << "LIEN : " <<numdc_l << "," <<numdc_c << std::endl ;
        if (numdc_l != numdc_c && numdc_l && numdc_c && a0) {
            int numval=p->numval ;
            float lien = static_cast<float> (100*mflux.tabval[numval].nb)/a0 ;
            mflux.tabval[numval].lien = lien ;
            // std::cout << numval << "/" << lien << std::endl ;
            if (lien > maxlien) {
                maxlien = lien ;
                dcmaxlien = numdc_c ;
            }
        }
    }
    vcom[numdc_l].maxlien = maxlien ;
    vcom[numdc_l].dcmaxlien = dcmaxlien ;
    vcom[numdc_l].status = 1 ;
} 

void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdc_c)
{
    element* p ;
    for (p = mflux.tete_c[numdc_c]; p != 0; p = p->next) {
        int numdc_l=p->numlc ;
        // std::cout << "LIEN_DUAL : " <<numdc_l << "," <<numdc_c << std::endl ;
        int a0 = vcom[numdc_l].act ;
        if (numdc_l != numdc_c && numdc_l && numdc_c && a0) {
            int numval=p->numval ;
            float lien = static_cast<float> (100*mflux.tabval[numval].nb)/a0 ;
            mflux.tabval[numval].lien = lien ;
            // std::cout << numval << "/" << lien << std::endl ;
            if (lien > vcom[numdc_l].maxlien) {
                vcom[numdc_l].maxlien = lien ;
                vcom[numdc_l].dcmaxlien = numdc_c ;
            }
        }
    }
} 
