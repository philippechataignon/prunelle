#include <vector>

#include "commune.h"
#include "matflux.h"
#include "lien.h"

void calcul_lien_a0(matflux & mflux, std::vector<commune> & vcom, int numdc_l)
{
    int a0 = vcom[numdc_l].act ;
    float maxlien = -1.0 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_l[numdc_l]; p != 0; p = p->next) {
        int numdc_c=p->numlc ;
            std::cout << "LIEN : " <<numdc_l << "," <<numdc_c << std::endl ;
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

void calcul_lien_dual_a0(matflux & mflux, std::vector<commune> & vcom, int numdc_c)
{
    element* p ;
    for (p = mflux.tete_c[numdc_c]; p != 0; p = p->next) {
        int numdc_l=p->numlc ;
        std::cout << "LIEN_DUAL : " <<numdc_l << "," <<numdc_c << std::endl ;
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

void calcul_lien_sta(matflux & mflux, std::vector<commune> & vcom, int numdc_l)
{
    int a0 = vcom[numdc_l].act ;
    int s0 = vcom[numdc_l].sta ;
    float maxlien = -100.0 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_l[numdc_l]; p != 0; p = p->next) {
        int numdc_c=p->numlc ;
        std::cout << "LIEN : " <<numdc_l << "," <<numdc_c << std::endl ; 
        if (numdc_l != numdc_c && numdc_l && numdc_c && a0) {
            int numval=p->numval ;
            int a1 = vcom[numdc_c].act ;
            float lien ;
            if (a1) {
                int s1 = vcom[numdc_c].sta ;
                int sab = s0 + s1 + mflux.tabval[numval].nb + mflux.get_val(numdc_c,numdc_l) ;
                float txsta_ab = static_cast<float> (100*sab) / (a0+a1) ;
                float txsta_a = static_cast<float> (100*s0) / a0 ;
                float txsta_b = static_cast<float> (100*s1) / a1 ;
                float txmax = txsta_a > txsta_b ? txsta_a : txsta_b ;
                lien = txsta_ab - txmax ;
            } else {
                lien = 0 ;
            }
            mflux.tabval[numval].lien = lien ;
            // std::cout << numval << "/" << lien << std::endl ;
            if (lien > vcom[numdc_l].maxlien) {
                vcom[numdc_l].maxlien = lien ;
                vcom[numdc_l].dcmaxlien = numdc_c ;
            }
        }
    }
    vcom[numdc_l].maxlien = maxlien ;
    vcom[numdc_l].dcmaxlien = dcmaxlien ;
    vcom[numdc_l].status = 1 ;
} 

void calcul_lien_dual_sta(matflux & mflux, std::vector<commune> & vcom, int numdc_c)
{
    element* p ;
    for (p = mflux.tete_c[numdc_c]; p != 0; p = p->next) {
        int numdc_l=p->numlc ;
        std::cout << "LIEN_DUAL : " <<numdc_l << "," <<numdc_c << std::endl ;
        int a0 = vcom[numdc_l].act ;
        int s0 = vcom[numdc_l].sta ;
        if (numdc_l != numdc_c && numdc_l && numdc_c && a0) {
            int numval=p->numval ;
            int a1 = vcom[numdc_c].act ;
            float lien ;
            if (a1) {
                int s1 = vcom[numdc_c].sta ;
                int sab = s0 + s1 + mflux.tabval[numval].nb + mflux.get_val(numdc_c,numdc_l) ;
                float txsta_ab = static_cast<float> (100*sab) / (a0+a1) ;
                float txsta_a = static_cast<float> (100*s0) / a0 ;
                float txsta_b = static_cast<float> (100*s1) / a1 ;
                float txmax = txsta_a > txsta_b ? txsta_a : txsta_b ;
                lien = txsta_ab - txmax ;
            } else {
                lien = 0 ;
            }
            mflux.tabval[numval].lien = lien ;
            // std::cout << numval << "/" << lien << std::endl ;
            if (lien > vcom[numdc_l].maxlien) {
                vcom[numdc_l].maxlien = lien ;
                vcom[numdc_l].dcmaxlien = numdc_c ;
            }
        }
    }
} 

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdc_l)
{
    calcul_lien_a0(mflux, vcom, numdc_l) ;
}

void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdc_c) {
    calcul_lien_dual_a0(mflux, vcom, numdc_c) ;
}
