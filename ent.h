#ifndef ent_h
#define ent_h

#include <iostream>

class ent
{
public:
    int numdc;
    ent *next;

    static const int VIDE = -1;
    ent () : numdc(VIDE) , next(0) {}
    ent (int w_numdc) : numdc(w_numdc) , next(0) {}
    ~ent () {}

    friend class listeent;
    friend std::ostream & operator << (std::ostream & os, const ent & ent);

    bool operator == (const ent & rhs) const {
        return numdc == rhs.numdc;
    }

    bool operator < (const ent & rhs) const {
        return numdc < rhs.numdc;
    }
}
;
#endif
