#ifndef VALEUR_H
#define VALEUR_H

#include <iosfwd>

class valeur
{

friend std::ostream & operator << (std::ostream & os, const valeur & valeur);
public:
    valeur () : nb(0), lien(0.0), calc(0) {}
    valeur (int w_nb) : nb(w_nb), lien(0.0), calc(0) {}
    ~valeur () {}

public:
    unsigned short   nb;
    float lien;
    bool calc ;
}
;
#endif
