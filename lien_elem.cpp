#include <vector>

#include "commune.h"
#include "matflux.h"
#include "lien_elem.h"

float 
calcul_lien_elem
(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d, const int type) 
{
    switch (type) {
        case 0 : return calcul_lien_elem_aa (mflux, vcom, numdc_l, numdc_c, nb, nb_d) ;
        case 1 : return calcul_lien_elem_sta(mflux, vcom, numdc_l, numdc_c, nb, nb_d) ;
        case 2 : return calcul_lien_elem_e0 (mflux, vcom, numdc_l, numdc_c, nb, nb_d) ;
        case 3 : return calcul_lien_elem_es0(mflux, vcom, numdc_l, numdc_c, nb, nb_d) ;
        case 4 : return calcul_lien_elem_a0 (mflux, vcom, numdc_l, numdc_c, nb, nb_d) ;
    }
    return 0;
}
        

float 
calcul_lien_elem_aa
(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)
{
    float lien = 0 ;
    int a0 = vcom[numdc_l].act ;
    if (a0) {
        lien = static_cast<float> (100*nb)/a0 ;
    }
    return lien ;
} 

float 
calcul_lien_elem_a0
(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)
{
    float lien = 0 ;
    int s0 = vcom[numdc_l].sor ;
    if (s0) {
        lien = static_cast<float> (100*nb)/s0 ;
    }
    return lien ;
} 

float 
calcul_lien_elem_sta
(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)
{
    float lien = 0;
        int a0 = vcom[numdc_l].act ;
        int s0 = vcom[numdc_l].sta ;
        int a1 = vcom[numdc_c].act ;
        int s1 = vcom[numdc_c].sta ;
    if (a0 && a1) {
        int sab = s0 + s1 + nb + nb_d ;
        float txsta_ab = static_cast<float> (100*sab) / (a0+a1) ;
        float txsta_a = static_cast<float>  (100*s0)  / a0 ;
        float txsta_b = static_cast<float>  (100*s1)  / a1 ;
        float txmax = txsta_a > txsta_b ? txsta_a : txsta_b ;
        lien = txsta_ab - txmax ;
        if (lien < 0) {
            lien = 0;
        }
    }
    return lien ;
}

float calcul_lien_elem_e0(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)
{
    float lien = 0;
    int a0 = vcom[numdc_l].act ;
    int a1 = vcom[numdc_c].act ;
    if (a0 && a1) {
        lien =  static_cast<float> (100* (nb + nb_d)) / (a0 + a1) ;
    } 
    return lien ;
}

float calcul_lien_elem_es0(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)
{
    float lien = 0 ;
    int s0 = vcom[numdc_l].sor ;
    int s1 = vcom[numdc_c].sor ;
    if (s0 && s1) {
        lien =  static_cast<float> (100* (nb + nb_d)) / (s0 + s1) ;
    } 
    return lien ;
}
