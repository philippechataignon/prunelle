#include "commune.h"

commune::commune (std::string w_nom):nom (w_nom)
{
    ent = sor = act = emp = sta = 0;
    status = 1;
    numdcmax = -1 ;
    lienmax = -1;
}

std::ostream & operator << (std::ostream & os, const commune & com)
{
    os << com.nom << "\t"  
       << "AcEmStEnSo : " << com.act << "/" << com.emp << "/"
       << com.sta << "/"  << com.ent << "/" << com.sor  << "\t"
       << "StDmLm : "     << com.status << "/" << com.numdcmax << "/" << com.lienmax << "\t"
       ;
    return os ;
}
