#ifndef commune_h
#define commune_h

#include <string>
#include <iostream>

class commune
{
public:
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

  std::string code;
  std::string nom;
  long ent, sor, sta, emp, act;
  short int status;
  int numdcmax ;
  float lienmax;
};
#endif
