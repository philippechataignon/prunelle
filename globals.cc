#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "commune.h"
#include "matflux.h"
#include "globals.h"

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
    std::cout << "Fin lecture fichier" << std::endl ;
}

void calcul_lien(matflux & mflux, std::vector<commune> & vcom, int numdca)
{
    int a0 = vcom[numdca].act ;
    int s0 = vcom[numdca].sta ;
    float maxlien = -1.0 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_l[numdca]; p != 0; p = p->next) {
        int numdcb=p->numlc ;
        if (numdca != numdcb && numdca && numdcb && a0) {
            int numval=p->numval ;
            int a1 = vcom[numdcb].act ;
            int s1 = vcom[numdcb].sta ;
            int sab = s0 + s1 + mflux.tabval[numval].nb + mflux.get_val(numdcb,numdca) ;

            float lien = static_cast<float> (100*sab) / (a0+a1) - static_cast<float>(100*s0)/a0 ;
            mflux.tabval[numval].lien = lien ;
            if (lien > maxlien) {
                maxlien = lien ;
                dcmaxlien = numdcb ;
            }
        }
    }
    vcom[numdca].maxlien = maxlien ;
    vcom[numdca].dcmaxlien = dcmaxlien ;
    vcom[numdca].status = 1 ;
} 

void calcul_lien_dual(matflux & mflux, std::vector<commune> & vcom, int numdca)
{
    int a0 = vcom[numdca].act ;
    int s0 = vcom[numdca].sta ;
    float maxlien = -1.0 ;
    int   dcmaxlien = -1 ;
    element* p ;
    for (p = mflux.tete_c[numdca]; p != 0; p = p->next) {
        int numdcb=p->numlc ;
        if (numdca != numdcb && numdca && numdcb && a0) {
            int numval=p->numval ;
            int a1 = vcom[numdcb].act ;
            int s1 = vcom[numdcb].sta ;
            int sab = s0 + s1 + mflux.tabval[numval].nb + mflux.get_val(numdcb,numdca) ;
            float lien = static_cast<float> (100*sab) / (a0+a1) - static_cast<float>(100*s1)/a1 ;
            mflux.tabval[numval].lien = lien ;
        }
    }
} 

void calcul_lien_init(matflux & mflux, std::vector<commune> & vcom)
{
    std::cout << "Calcul des liens init" << std::endl ;
    for (int i=0; i<vcom.size(); i++) {
        calcul_lien(mflux, vcom, i) ;
    }
}

void calcul_lien_maj(matflux & mflux, std::vector<commune> & vcom)
{
    std::cout << "Calcul des liens maj" << std::endl ;
    for (int i=0; i<vcom.size(); i++) {
        if (vcom[i].status == 2) {
            calcul_lien(mflux, vcom, i) ;
            calcul_lien_dual(mflux, vcom, i) ;
        }
    }
}

void agrege(matflux & mflux, std::vector<commune> & vcom, int numdca, int numdcb) 
{
    std::cout << "Agrégation" << std::endl ;
    int nab = mflux.get_val(numdca,numdcb) ;
    int nba = mflux.get_val(numdcb,numdca) ;
    vcom[numdca].sta += vcom[numdcb].sta + nab + nba ;
    vcom[numdca].ent += (vcom[numdcb].ent - nab - nba) ;
    vcom[numdca].sor += (vcom[numdcb].sor - nab - nba) ;
    vcom[numdca].emp = vcom[numdca].sta + vcom[numdca].ent;
    vcom[numdca].act = vcom[numdca].sta + vcom[numdca].sor;
    mflux.merge(numdca,numdcb) ;
    prepare_calcul_max(mflux, vcom, numdca, numdcb) ;
    vcom[numdcb].status = 0 ;
}

void prepare_calcul_max(matflux & mflux, std::vector<commune> & vcom, int numdca, int numdcb)
{
    element* p ;
    vcom[numdca].status = 2 ;
    for (p = mflux.tete_l[numdca]; p != 0; p = p->next) {
        vcom[p->numlc].status = 2 ;
    }
    for (p = mflux.tete_c[numdca]; p != 0; p = p->next) {
        vcom[p->numlc].status = 2 ;
    }
    for (p = mflux.tete_l[numdcb]; p != 0; p = p->next) {
        vcom[p->numlc].status = 2 ;
    }
    for (p = mflux.tete_c[numdcb]; p != 0; p = p->next) {
        vcom[p->numlc].status = 2 ;
    }
    
    int cpt = 0 ;
    for (int i=0; i<vcom.size(); i++) {
        if (vcom[i].status == 2) {
            cpt++ ;
        }
    }
    std::cout << "Nb de com en statut 2 : " << cpt << std::endl ;
}
