#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "commune.h"
#include "matflux.h"

void lecture_flux (std::ifstream & in, matflux & mflux, std::vector<commune> & vcom, int nbflux, int nbcom)
{
    std::cout << "\nDébut lecture fichier flux" << std::endl ;
    std::string nom ;
    for (int i=0 ; i<nbcom  ; i++) {
        in >> nom ;
        vcom.push_back(commune(nom)) ;
    }
    int numdcr, numdclt, nb ;
    for (int i=0 ; i<nbflux ; i++) {
        in >> numdcr >> numdclt >> nb ;
        mflux.set_val(numdcr, numdclt, nb) ;
    }
    std::cout << "\nFin lecture fichier flux" << std::endl ;
}
