#ifndef commune_h
#define commune_h

#include <string>
#include <iostream>

class commune
{
public:
  commune (std::string w_nom = "");

  bool operator == (const commune & rhs) const {
    return nom == rhs.nom;
  }
  bool operator < (const commune & rhs) const
  {
    return nom < rhs.nom;
  }

  friend std::ostream & operator << (std::ostream & os,
				     const commune & commune);

  std::string nom;
  long ent, sor, sta, emp, act;
  short int status;
  int numdcmax ;
  float lienmax;
};
#endif
