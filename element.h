#ifndef ELEMENT_H
#define ELEMENT_H

#include <iosfwd>

class element
{
public:
    element() : numlc(0), numval(0) {}
    element (int w_numlc, int w_numval) : numlc(w_numlc), numval(w_numval), next(0) {}

    bool operator == (const element & rhs) const {
        return (numlc == rhs.numlc) ;
    }

    bool operator < (const element & rhs) const {
        return (numlc < rhs.numlc) ;
    }

friend std::ostream & operator << (std::ostream & os, const element & element);

public:
    unsigned short int   numlc  ;
    int   numval ;
    element* next ;
}
;

#endif
