#include <vector>

#include "commune.h"
#include "matflux.h"
#include "lien_es.h"

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
