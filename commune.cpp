#include <ostream>
#include "commune.h"

commune::commune(std::string w_nom):nom(w_nom)
{
    ent = sor = act = emp = sta = 0;
    mi  = si  = 0 ;
    status = 1;
    dcmaxlien = -1 ;
    maxlien = -1.0;
    nbagreg = 1 ;
}

std::ostream & operator << (std::ostream & os, const commune & com)
{
    os << com.nom << "\t"  
       << "AcEmStEnSo : " << com.act << "/" << com.emp << "/"
       << com.sta << "/"  << com.ent << "/" << com.sor  << "\t"
       << "Mi/Si : " << com.mi << "/" << com.si << "\t" 
       << "StDmLmAg : "   << com.status << "/" << com.dcmaxlien << "/" 
       << com.maxlien << "/" << com.nbagreg
       ;
    return os ;
}
