#include <vector>

#include "commune.h"
#include "matflux.h"
#include "lien.h"

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int type)
{
    float maxlien = -1e40 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_l[numdc_l]; p != 0; p = p->next) {
        int numdc_c=p->numlc ;
        //    std::cout << "LIEN : " <<numdc_l << "," <<numdc_c << std::endl ;
        if (numdc_l != numdc_c && numdc_l && numdc_c) {
            int numval=p->numval ;
            float lien = calcul_lien_elem(mflux, vcom, numdc_l, numdc_c, mflux.tabval[numval].nb, type) ;
            mflux.tabval[numval].lien = lien ;
            if (lien > maxlien ||
                    (dcmaxlien != -1 && lien>= maxlien - 1e-3 && vcom[numdc_c].act > vcom[dcmaxlien].act)
               ) {
                maxlien = lien ;
                dcmaxlien = numdc_c ;
            }
        }
    }
    vcom[numdc_l].maxlien = maxlien ;
    vcom[numdc_l].dcmaxlien = dcmaxlien ;
    vcom[numdc_l].status = 1 ;
}

void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdc_c, int type) {
    element* p ;
    for (p = mflux.tete_c[numdc_c]; p != 0; p = p->next) {
        int numdc_l=p->numlc ;
        //std::cout << "LIEN_DUAL : " <<numdc_l << "," <<numdc_c << std::endl ;
        if (numdc_l != numdc_c && numdc_l && numdc_c) {
            int numval=p->numval ;
            float lien = calcul_lien_elem(mflux, vcom, numdc_l, numdc_c, mflux.tabval[numval].nb,type) ;
            mflux.tabval[numval].lien = lien ;
            if (lien > vcom[numdc_l].maxlien ||
                    (vcom[numdc_l].dcmaxlien != -1 
                        && lien >= vcom[numdc_l].maxlien - 1e-3 
                        && vcom[numdc_c].act > vcom[vcom[numdc_l].dcmaxlien].act
                    )
               ) {
                vcom[numdc_l].maxlien = lien ;
                vcom[numdc_l].dcmaxlien = numdc_c ;
            }
        }
    }
}

float calcul_lien_elem(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, const int type) {
    switch (type) {
        case 0 :
        {
            return calcul_lien_elem_a0(mflux, vcom, numdc_l, numdc_c, nb) ;
            break ;
        }
        case 1 :
        {
            return calcul_lien_elem_sta(mflux, vcom, numdc_l, numdc_c, nb) ;
            break ;
        }
        default:
        {
            std::cerr << "Erreur type de lien" << std::endl ;
            exit(1) ;
        }
    }
}
        

float calcul_lien_elem_a0(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb)
{
    float lien ;
    int a0 = vcom[numdc_l].act ;
    if (a0) {
        lien = static_cast<float> (100*nb)/a0 ;
    } else {
        lien = 0 ;
    }
    return lien ;
} 

float calcul_lien_elem_sta(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb)
{
    float lien ;
        int a0 = vcom[numdc_l].act ;
        int s0 = vcom[numdc_l].sta ;
        int a1 = vcom[numdc_c].act ;
        int s1 = vcom[numdc_c].sta ;
    if (a0 && a1) {
        int sab = s0 + s1 + nb + mflux.get_val(numdc_c,numdc_l) ;
        float txsta_ab = static_cast<float> (100*sab) / (a0+a1) ;
        float txsta_a = static_cast<float> (100*s0) / a0 ;
        float txsta_b = static_cast<float> (100*s1) / a1 ;
        float txmax = txsta_a > txsta_b ? txsta_a : txsta_b ;
        lien = txsta_ab - txmax ;
    } else {
        lien = 0 ;
    }
    return lien ;
}
