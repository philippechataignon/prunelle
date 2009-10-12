#ifndef VALEUR_H
#define VALEUR_H

#include <iosfwd>

class valeur
{

friend std::ostream & operator << (std::ostream & os, const valeur & valeur);
public:
    valeur () : nb(0.0), lien(0.0), calc(0) {}
    valeur (double w_nb) : nb(w_nb), lien(0.0), calc(0) {}
    ~valeur () {}

public:
    double nb;
    double lien;
    bool calc ;
}
;
#endif
