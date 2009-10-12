#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "commune.h"
#include "matflux.h"
#include "lien.h"
#include "utils.h"

void lecture_fich (std::istream & in, matflux & mflux, std::vector<commune> & vcom)
{
    int nbflux = mflux.get_nbval() ;
    int nbcom  = mflux.get_dim()   ;
    int avt = 0 ;
    int last_avt = -1 ;

    std::cerr << "Lecture zones" << std::endl ;
    std::string nom ;
    int tmp ;
    for (int i=0 ; i<nbcom  ; i++) {
        in >> tmp >> nom ;
        // std::cerr << nom << std::endl ;
        vcom.push_back(commune(nom)) ;
    }
    int numdcr, numdclt ;
    double nb ;
    std::cerr << "Lecture flux :" << std::endl ;
    for (int i=0; i<nbflux; i++) {
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
            std::cerr << ".";
            last_avt = avt ;
        }
    }
    std::cerr << std::endl ;
}

void agrege(matflux & mflux, std::vector<commune> & vcom, int numdca, int numdcb) 
{
    // std::cout << "Agrégation" << std::endl ;
    // migrants internes = flux ab + flux ba
    double mi  = mflux.get_val(numdca,numdcb).nb + mflux.get_val(numdcb,numdca).nb ;

    vcom[numdca].mi  += vcom[numdcb].mi + mi ;
    vcom[numdca].si  += vcom[numdcb].si ;
    vcom[numdca].ent += vcom[numdcb].ent - mi ;
    vcom[numdca].sor += vcom[numdcb].sor - mi ;

    vcom[numdca].sta = vcom[numdca].si  + vcom[numdca].mi ;
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
    vcom[numdca].maxlien =  0 ;
    vcom[numdca].dcmaxlien =  0;
}
