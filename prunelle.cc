#include <fstream>
#include <vector>

#include "globals.h"
#include "commune.h"
#include "matflux.h"

int main(int argc, char* argv[])
{
    std::cout << "Prunelle V 8.00 - " << __DATE__ << " - " << __TIME__ <<
        std::endl;

    if (argc != 3 ) {
        std::cout << "Entrer fichier prunelle, fichier sortie et type de lien\n";
        std::cout << "Types de lien :\n";
        std::cout << "0 : flux(A,B)/act(A)\n1 : (flux(A,B)+flux(B,A)/act(A)+act(B))\n2 : flux(A,B)/sor(A)\n" ;
        std::exit (0);
    }

    std::ifstream in (argv[1]);
    if (in == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier prunelle" << std::endl ;
        exit(1);
    }

    std::ofstream out (argv[2]);
    if (out == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
        exit(1);
    }

    int nbcom, nbflux ;
    in >> nbflux ;
    in >> nbcom ;
    std::cout << nbflux << "/" << nbcom << std::endl ;

    std::vector<commune> vcom ;
    vcom.reserve(nbcom) ;
    matflux mflux (nbcom,nbflux);
    lecture_fich (in, mflux, vcom);
    calcul_lien(mflux,vcom) ;

    for(int i=0 ; i<nbcom; i++) {
        std::cout << vcom[i] << std::endl ;
    }

    mflux.imprime() ;
}
