//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop

#include "flux.h"
std::ostream & operator << (std::ostream & os, const flux & flux)
{
  os << "Flux\t" << &flux << "\t" ;
  if ( &flux != 0)
  {
    std::cout  << flux.numdclt << "\t" << flux.nb << "\t"
        << flux.lien << "\t" << flux.next;
  }
  return os;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
