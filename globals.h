#ifndef GLOBALS_H
#define GLOBALS_H
#include <vector>
#include <fstream>
#include "matflux.h"
#include "commune.h"
void lecture_commune(std::vector<commune> & vcom , std::ifstream & com);
void lecture_flux (matflux & mflux,  std::ifstream & flu, std::vector<commune> & vcom);
#endif
