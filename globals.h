#ifndef GLOBALS_H
#define GLOBALS_H
#include <vector>
#include <fstream>
#include "matflux.h"
#include "commune.h"

void agrege(matflux & mflux, std::vector<commune> & vcom, int numdca, int numdcb) ;
void calcul_lien_init(matflux & mflux, std::vector<commune> & vcom);
void calcul_lien_maj(matflux & mflux, std::vector<commune> & vcom);
void lecture_fich (std::ifstream & in, matflux & mflux, std::vector<commune> & vcom);
void prepare_calcul_max(matflux & mflux, std::vector<commune> & vcom, int numdca, int numdcb);
#endif
