#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

#include "commune.h"
#include "matflux.h"
int verbeux = 0;
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
    std::cout << "Fin lecture fichier flux (Passe 1)" << std::endl ;
    nbflux-- ;
    std::cout << "Nb flux non nuls : " << nbflux << " - Taille : " << set_com.size() << std::endl ;

    // out << "# PRUNELLE" << "\n" ;
    // out << "# Nombre de flux" << "\n" ;
    out << nbflux << "\n" ;
    // out << "# Nombre de zones" << "\n" ;
    out << set_com.size() << "\n" ;
    // out << "# Liste des " << set_com.size() << " zones : num code" << "\n" ;

    for (std::set<std::string>::iterator i=set_com.begin() ; i != set_com.end() ; i++) {
        out << std::distance(set_com.begin(),i) << "\t" << *i << "\n" ;
    }

    // out << "# Liste des " << nbflux << " flux : numr numlt nb" << "\n" ;
    flu.clear() ;
    flu.seekg (0) ;

    std::vector<std::string> vcom ;
    vcom.reserve(set_com.size()) ;

    std::copy(set_com.begin(), set_com.end(), back_inserter(vcom)) ;
    
    std::cout << "Début lecture fichier flux (Passe2)" << std::endl ;
    int cpt = 0 ;
    int avt = 0 ;
    int last_avt = 0 ;
    while (flu) {
        std::string coder;
        std::string codelt;
        int nb;
        flu >> coder >> codelt >> nb;

        if (!coder.empty () && nb!= 0) {
            //std::set<std::string>::iterator r = set_com.find(coder) ;
            //std::set<std::string>::iterator lt = set_com.find(codelt) ;
            int numdcr =  std::distance(vcom.begin(), lower_bound(vcom.begin(), vcom.end(),coder)) ;
            int numdclt=  std::distance(vcom.begin(), lower_bound(vcom.begin(), vcom.end(),codelt)) ;
            //int numdcr  = set_com.find(coder) ;
            //int numdclt = set_com.find(codelt) ;
            out << numdcr << "\t" << numdclt << "\t" << nb << "\n" ; 
            cpt++ ;
        }
        avt = (100 * cpt) / nbflux ;
        if (avt != last_avt) {
            std::cout << "Avancement : " << avt << "%" << std::endl ;
            last_avt = avt ;
        }
    }
    std::cout << "Fin lecture fichier flux" << std::endl ;
}
