#ifndef VALEUR_H
#define VALEUR_H

#include <iosfwd>

class valeur
{

friend std::ostream & operator << (std::ostream & os, const valeur & valeur);
public:
    valeur () : nb(0), lien(0.0) {}
    valeur (int w_val) : nb(w_val), lien(0.0) {}
    ~valeur () {}

public:
    int   nb;
    float lien;
}
;
#endif
