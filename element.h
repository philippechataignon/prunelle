#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>

class element
{
public:
    element() : numlc(-1), numval(-1) {}
    element (int w_numlc, int w_numval) : numlc(w_numlc), numval(w_numval) {}

    
    element(const element & rhs) {
        numlc  =    rhs.numlc ;
        numval = rhs.numval ;
    }

    bool operator == (const element & rhs) const {
        return (numlc == rhs.numlc) ;
    }

    bool operator < (const element & rhs) const {
        return (numlc < rhs.numlc) ;
    }

friend std::ostream & operator << (std::ostream & os, const element & element);

public:
    int   numlc  ;
    int   numval ;
}
;

#endif
