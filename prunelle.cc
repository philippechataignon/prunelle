#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cmath>

#include "globals.h"
#include "commune.h"
#include "matflux.h"

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
}
