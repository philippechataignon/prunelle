//---------------------------------------------------------------------------
#ifndef communeH
#define communeH

#include <set>
#include <string>
#include <iostream>

#include "flux.h"

class commune
{

public:
  std::string code;
  std::string nom;
  long ent, sor, sta, emp, act;
  short int status;
  int numdcmax ;
  float lienmax;

  commune (std::string w_code = "00000", std::string w_nom = "");

  bool operator == (const commune & rhs) const {
    return code == rhs.code;
  }
  bool operator < (const commune & rhs) const
  {
    return code < rhs.code;
  }
  bool operator != (const commune & rhs) const
  {
    return code != rhs.code;
  }

  friend std::ostream & operator << (std::ostream & os,
				     const commune & commune);
};
//---------------------------------------------------------------------------
#endif

