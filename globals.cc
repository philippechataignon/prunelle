#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "commune.h"
#include "matflux.h"

void lecture_fich (std::ifstream & in, matflux & mflux, std::vector<commune> & vcom)
{
    int nbflux = mflux.get_nbval() ;
    int nbcom  = mflux.get_dim()   ;
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

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdca)
{
    std::cout << "Calcul des liens pour " << vcom[numdca].nom << std::endl ;
    int a0 = vcom[numdca].act ;
    int s0 = vcom[numdca].sta ;
    element* p ;
    for (p = mflux.tete_l[numdca]; p != 0; p = p->next) {
        int numdcb=p->numlc ;
        int numval=p->numval ;
        int a1 = vcom[numdcb].act ;
        int s1 = vcom[numdcb].sta ;
        int sab = s0 + s1 + mflux.tabval[numval].nb + mflux.get_val(numdcb,numdca) ;

        mflux.tabval[numval].lien = static_cast<float> (sab) / (a0+a1) - static_cast<float>(s0)/a0 ;
    }
} 

void calcul_lien(matflux & mflux, std::vector<commune> & vcom)
{
    for (int i=0; i<vcom.size(); i++) {
        calcul_lien(mflux, vcom, i) ;
    }
}
