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
