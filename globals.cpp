#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "commune.h"
#include "matflux.h"
#include "globals.h"
#include "lien.h"

void lecture_fich (std::ifstream & in, matflux & mflux, std::vector<commune> & vcom)
{
    int nbflux = mflux.get_nbval() ;
    int nbcom  = mflux.get_dim()   ;
    int avt = 0 ;
    int last_avt = -1 ;
    
    std::cout << "Lecture zones" << std::endl ;
    std::string nom ;
    int tmp ;
    
    for (int i=0 ; i<nbcom  ; i++) {
        in >> tmp >> nom ;
        // std::cout << nom << std::endl ;
        vcom.push_back(commune(nom)) ;
    }
    int numdcr, numdclt, nb ;
    std::cout << "Lecture flux :" << std::endl ;
    for (int i=0 ; i<nbflux ; i++) {
        in >> numdcr >> numdclt >> nb ;
        mflux.set_val(numdcr, numdclt, nb) ;
        if (numdcr != numdclt) {
            vcom[numdcr].sor += nb;
            vcom[numdcr].act += nb;
            vcom[numdclt].ent += nb;
            vcom[numdclt].emp += nb;
        } else {
            vcom[numdcr].si  += nb;
            vcom[numdcr].sta += nb;
            vcom[numdcr].act += nb;
            vcom[numdcr].emp += nb;
        }
        avt = (100 * i) / nbflux ;
        if (avt != last_avt) {
            std::cout << avt << "% ";
            std::cout.flush() ;
            last_avt = avt ;
        }
    }
}

void agrege(matflux & mflux, std::vector<commune> & vcom, int numdca, int numdcb) 
{
    // std::cout << "Agrégation" << std::endl ;
    // migrants internes = flux ab + flux ba
    int mi  = mflux.get_val(numdca,numdcb) + mflux.get_val(numdcb,numdca) ;

    vcom[numdca].mi  += vcom[numdcb].mi + mi ;
    vcom[numdca].si  += vcom[numdcb].si ;
    vcom[numdca].ent += vcom[numdcb].ent - mi ;
    vcom[numdca].sor += vcom[numdcb].sor - mi ;

    vcom[numdca].sta =  vcom[numdca].si + vcom[numdca].mi ;
    vcom[numdca].emp = vcom[numdca].sta + vcom[numdca].ent;
    vcom[numdca].act = vcom[numdca].sta + vcom[numdca].sor;

    mflux.merge(numdca,numdcb) ;
    vcom[numdca].nbagreg++ ;
    for (unsigned int i=0; i<vcom.size(); i++) {
        if (vcom[i].status && vcom[i].dcmaxlien==numdcb) {
            vcom[i].dcmaxlien=numdca ;
        }
    }
    vcom[numdcb].status = 0 ;
}

void help()
{
}
