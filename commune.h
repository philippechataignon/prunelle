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
  // status : 0 inactive ; 1 active avec max � jour ; 2 active avec max � calculer
  short int status;
  int   dcmaxlien ;
  float maxlien;
};
#endif
