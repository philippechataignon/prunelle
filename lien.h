#ifndef LIEN_H
#define LIEN_H

#include <vector>

#include "commune.h"
#include "matflux.h"

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdca, const int type);
void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdca, const int type);
#endif
