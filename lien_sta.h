#include <vector>

#include "commune.h"
#include "matflux.h"

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdca);
void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdca);
