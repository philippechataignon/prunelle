#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "commune.h"
#include "matflux.h"

void lecture_commune(std::vector<commune> & vcom , std::ifstream & com)
{
    std::cout << "Début lecture fichier nom des communes" << std::endl;
    while (com) {
        std::string code;
        std::string nom;
        com >> code;
        com >> std::ws >> nom;

        if (!code.empty ())
            vcom.push_back (commune (code, nom));
    }
    std::cout << "Fin lecture fichier nom des communes" << std::endl;
}

  
void lecture_flux (matflux & mflux,  std::ifstream & flu, std::vector<commune> & vcom)
{
    std::cout << "\nDébut lecture fichier flux" << std::endl ;
    unsigned int ii=0 ;
    while (flu) {
        std::string coder;
        std::string codelt;
        int nb;

        typedef std::vector<commune>::iterator viter ;
        typedef std::pair<viter,viter> piter ;

        flu >> coder >> codelt >> nb;

        if (!coder.empty ()) {
            piter icomr = std::equal_range (vcom.begin (), vcom.end (), commune (coder));
            if (icomr.first == icomr.second) {
                std::cout << "Commune de résidence non trouvée : " << coder << "\n";
            } else {  
                piter icomlt = std::equal_range (vcom.begin (), vcom.end (), commune (codelt));
                if (icomlt.first == icomlt.second) {
                    std::cout << "Commune de lieu de travail non trouvée : " << codelt << "\n";
                } else {
                    int numdcr = std::distance (vcom.begin (), icomr.first) ;
                    int numdclt = std::distance (vcom.begin (), icomlt.first) ;
                    mflux.set_val (numdcr, numdclt , nb); 
                }
            }

            if ( ii % 1000 == 0 ) {
                std::cout << "." ;
                std::cout.flush();
            }
            ii++;
        }
    }
    std::cout << "\nFin lecture fichier flux" << std::endl ;
}
