#ifndef GLOBALS_H
#define GLOBALS_H
#include <vector>
#include <fstream>
#include "matflux.h"
#include "commune.h"

void lecture_fich (std::ifstream & in, matflux & mflux, std::vector<commune> & vcom, int nbflux, int nbcom);

#endif
