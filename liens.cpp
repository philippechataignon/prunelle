#include <iostream>
#include <vector>

#include "commune.h"
#include "matflux.h"
#include "liens.h"

double lien_aa::calcul_elem(int numdc_l, int numdc_c, double nb, double nb_d)
{
    double lien = 0;
    double a0 = vcom[numdc_l].act;
    if (a0) {
        lien = static_cast < double >(100 * nb) / a0;
    }
    // std::cout<<numdc_l<<"\t"<<numdc_c<<"\t"<<nb<<"\t"<<nb_d<<"\t"<<lien<<std::endl ;
    return lien;
}

double lien_es::calcul_elem(int numdc_l, int numdc_c, double nb, double nb_d)
{
    double lien = 0;
    double s0 = vcom[numdc_l].sor;
    double s1 = vcom[numdc_c].sor;
    if (s0 && s1) {
        lien = static_cast < double >(100 * (nb + nb_d)) / (s0 + s1);
    }
    // std::cout<<numdc_l<<"\t"<<numdc_c<<"\t"<<nb<<"\t"<<nb_d<<"\t"<<lien<<std::endl ;
    return lien;
}

double lien_phc::calcul_elem(int numdc_l, int numdc_c, double nb, double nb_d)
{
    double lien = 0;
    lien = nb;
    if (lien < 0) {
        lien = 0;
    }
    return lien;
}

double lien_sta::calcul_elem(int numdc_l, int numdc_c, double nb, double nb_d)
{
    double lien = 0;
    double a0 = vcom[numdc_l].act;
    double s0 = vcom[numdc_l].sta;
    double a1 = vcom[numdc_c].act;
    double s1 = vcom[numdc_c].sta;
    if (a0 && a1) {
        double sab = s0 + s1 + nb + nb_d;
        double txsta_ab = static_cast < double >(100 * sab) / (a0 + a1);
        double txsta_a = static_cast < double >(100 * s0) / a0;
        double txsta_b = static_cast < double >(100 * s1) / a1;
        double txmax = txsta_a > txsta_b ? txsta_a : txsta_b;
        lien = txsta_ab - txmax;
        if (lien < 0) {
            lien = 0;
        }
    }
    // std::cout<<numdc_l<<"\t"<<numdc_c<<"\t"<<nb<<"\t"<<nb_d<<"\t"<<lien<<std::endl ;
    return lien;
}
