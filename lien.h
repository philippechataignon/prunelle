#include <vector>

#include "commune.h"
#include "matflux.h"

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdca, const int type);
void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdca, const int type);
float calcul_lien_elem(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int numval, int type) ;
float calcul_lien_elem_sta(matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int numval) ;
float calcul_lien_elem_a0 (matflux & mflux, std::vector<commune> & vcom, int numdc_l, int numdc_c, int numval)  ;
