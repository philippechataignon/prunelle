#include <vector>

#include "commune.h"
#include "matflux.h"
#include "liens.h"

float lien_aa::calcul_elem(int numdc_l, int numdc_c, int nb, int nb_d)
{
    float lien = 0 ;
    int a0 = vcom[numdc_l].act ;
    if (a0) {
        lien = static_cast<float> (100*nb)/a0 ;
    }
    return lien ;
} 

float lien_es::calcul_elem(int numdc_l, int numdc_c, int nb, int nb_d)
{
    float lien = 0 ;
    int s0 = vcom[numdc_l].sor ;
    int s1 = vcom[numdc_c].sor ;
    if (s0 && s1) {
        lien =  static_cast<float> (100* (nb + nb_d)) / (s0 + s1) ;
    }
    return lien ;
}



float lien_sta::calcul_elem(int numdc_l, int numdc_c, int nb, int nb_d)
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
