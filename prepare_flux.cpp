#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

#include "commune.h"
#include "matflux.h"

int main(int argc, char* argv[])
{
    std::cout << "Prépare_flux v1.00 - " << __DATE__ << " - " << __TIME__ <<
        std::endl;

    if (argc != 3 ) {
        std::cout << "Entrer fichier couple et fichier sortie \n";
        std::exit (0);
    }

    std::ifstream flu (argv[1]);
    if (flu == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier couple" << std::endl ;
        exit(1);
    }

    std::ofstream out (argv[2]);
    if (out == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
        exit(1);
    }

    std::set <std::string> set_com;

    std::cout << "Début lecture fichier flux (Passe 1)" << std::endl ;

    std::string coder;
    std::string codelt;
    int nb;

    int nbflux = 0 ;
    set_com.insert("*****") ;
    while (flu) {
        flu >> coder >> codelt >> nb;
        if (!coder.empty () && nb!= 0) {
            nbflux++ ;
            set_com.insert(coder) ;
            set_com.insert(codelt) ;
        }
    }
    
    nbflux-- ;
    std::cout << "Nb flux non nuls : " << nbflux << " - Taille : " << set_com.size() << std::endl ;
    std::cout << "Ecriture liste communes" << std::endl ;

    out << nbflux << "\n" ;
    out << set_com.size() << "\n" ;

    int i = 0 ;
    for (std::set<std::string>::iterator p=set_com.begin() ; p != set_com.end() ; p++) {
        out << i << "\t" << *p << "\n" ;
        i++ ;
    }
    
    flu.clear() ;
    flu.seekg (0) ;

    std::vector<std::string> vcom ;
    vcom.reserve(set_com.size()) ;

    std::copy(set_com.begin(), set_com.end(), back_inserter(vcom)) ;
    
    std::cout << "Début lecture fichier flux (Passe2)" << std::endl ;
    while (flu) {
        std::string coder;
        std::string codelt;
        int nb;
        flu >> coder >> codelt >> nb;

        if (!coder.empty () && nb!= 0) {
            out <<  std::distance(vcom.begin(), lower_bound(vcom.begin(), vcom.end(),coder)) 
                << "\t"
                <<  std::distance(vcom.begin(), lower_bound(vcom.begin(), vcom.end(),codelt)) 
                << "\t" << nb << "\n" ; 
                ;
        }
    }
    std::cout << "Fin lecture fichier flux" << std::endl ;
}
