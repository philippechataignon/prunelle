#ifndef LIEN_ELEM_H
#define LIEN_ELEM_H

#include <vector>
#include "commune.h"
#include "matflux.h"

float calcul_lien_elem
(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d, const int type) ;
float calcul_lien_elem_aa (matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)  ;
float calcul_lien_elem_sta(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)  ;
float calcul_lien_elem_a0 (matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)  ;
float calcul_lien_elem_e0 (matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)  ;
float calcul_lien_elem_es0(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int nb, int nb_d)  ;
#endif
