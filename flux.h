#ifndef flux_h
#define flux_h

#include <iostream>

class flux
{
public:
    int numdclt;
    int nb;
    float lien;
    flux *next;

public:
    static const int VIDE = -1;
    flux () : numdclt(VIDE) , nb(0) , lien(0), next(0) {}
    flux (int w_numdclt, int w_nb):
        numdclt(w_numdclt) , nb(w_nb) , lien(0), next(0) {}
    ~flux () {}

    friend class listeflux;
    friend std::ostream & operator << (std::ostream & os, const flux & flux);

    bool operator == (const flux & rhs) const {
        return lien == rhs.lien;
    }

    bool operator < (const flux & rhs) const {
        return lien < rhs.lien;
    }
}

 ;

//---------------------------------------------------------------------------
#endif
