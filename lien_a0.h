#include <vector>

#include "commune.h"
#include "matflux.h"

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdca);
void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdca);

void calcul_lien_sta(matflux & mflux, std::vector<commune> & vcom, int numdca);
void calcul_lien_dual_sta(matflux & mflux, std::vector<commune> & vcom, int numdca);
void calcul_lien_a0(matflux & mflux, std::vector<commune> & vcom, int numdca);
void calcul_lien_dual_a0(matflux & mflux, std::vector<commune> & vcom, int numdca);
