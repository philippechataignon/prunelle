#ifndef UTILS_H
#define UTILS_H
#include <iosfwd>
#include <vector>
#include "matflux.h"
#include "commune.h"

void agrege(matflux & mflux, std::vector<commune> & vcom, int numdca, int numdcb) ;
void lecture_fich (std::ifstream & in, matflux & mflux, std::vector<commune> & vcom);
#endif