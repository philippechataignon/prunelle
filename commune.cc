#include "commune.h"

commune::commune (std::string w_nom):nom (w_nom)
{
    ent = sor = act = emp = sta = 0;
    status = 2;
    dcmaxlien = -1 ;
    maxlien = -1.0;
}

std::ostream & operator << (std::ostream & os, const commune & com)
{
    os << com.nom << "\t"  
       << "AcEmStEnSo : " << com.act << "/" << com.emp << "/"
       << com.sta << "/"  << com.ent << "/" << com.sor  << "\t"
       << "StDmLm : "     << com.status << "/" << com.dcmaxlien << "/" << com.maxlien << "\t"
       ;
    return os ;
}
