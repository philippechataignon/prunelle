#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "commune.h"
#include "matflux.h"

void lecture_fich (std::ifstream & in, matflux & mflux, std::vector<commune> & vcom, int nbflux, int nbcom)
{
    std::cout << "Lecture zones" << std::endl ;
    std::string nom ;
    int tmp ;
    for (int i=0 ; i<nbcom  ; i++) {
        in >> tmp >> nom ;
        // std::cout << nom << std::endl ;
        vcom.push_back(commune(nom)) ;
    }
    int numdcr, numdclt, nb ;
    std::cout << "Lecture flux" << std::endl ;
    for (int i=0 ; i<nbflux ; i++) {
        in >> numdcr >> numdclt >> nb ;
        mflux.set_val(numdcr, numdclt, nb) ;
        if (numdcr != numdclt) {
            vcom[numdcr].sor += nb;
            vcom[numdcr].act += nb;
            vcom[numdclt].ent += nb;
            vcom[numdclt].emp += nb;
        } else {
            vcom[numdcr].sta += nb;
            vcom[numdcr].act += nb;
            vcom[numdcr].emp += nb;
        }
    }
    std::cout << "Fin lecture fichier" << std::endl ;
}
