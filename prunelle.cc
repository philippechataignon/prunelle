#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cmath>

#include "commune.h"
#include "matflux.h"
#include "prunelle.h"

int main(int argc, char* argv[])
{
    std::cout << "Prunelle V 8.00 - " << __DATE__ << " - " << __TIME__ <<
        std::endl;

    if (argc != 5 && argc != 6) {
        std::cout << "Entrer fichier couple, fichier nom,fichier sortie et type de lien\n";
        std::cout << "Types de lien :\n";
        std::cout << "0 : flux(A,B)/act(A)\n1 : (flux(A,B)+flux(B,A)/act(A)+act(B))\n2 : flux(A,B)/sor(A)\n" ;
        std::exit (0);
    }

    std::ifstream flu (argv[1]);
    if (flu == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier couple" << std::endl ;
        exit(1);
    }

    std::ifstream com (argv[2]);
    if (com == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier des noms" << std::endl ;
        exit(1);
    }

    std::ofstream out (argv[3]);
    if (out == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
        exit(1);
    }

    std::vector < commune > vcom;
    lecture_commune (vcom , com) ;

    int nbflux ;
    flu >> nbflux ;

    matflux mflux (vcom.size(),nbflux);
    lecture_flux (mflux ,flu, vcom);

    mflux.merge(1,2);
    mflux.merge(1,3);
    mflux.merge(1,4);
}

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
