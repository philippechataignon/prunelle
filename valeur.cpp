#include <iostream>
#include "valeur.h"

std::ostream & operator << (std::ostream & os, const valeur & valeur)
{
    std::cout << "{" << valeur.nb << "," << valeur.lien << "}" ;
    return os;
}

