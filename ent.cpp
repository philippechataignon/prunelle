//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop

#include "ent.h"
std::ostream & operator << (std::ostream & os, const ent & ent)
{
  os << "Entrants : " << &ent << "\t" ;
  if ( &ent != 0)
  {
    std::cout  << ent.numdc << "\t" << ent.next << "\t" ;
  }
  return os;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
