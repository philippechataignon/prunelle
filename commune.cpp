#include "commune.h"

commune::commune (std::string w_code, std::string w_nom):code (w_code), nom (w_nom)
{
    ent = sor = act = emp = sta = 0;
    status = 1;
    numdcmax = -1 ;
    lienmax = -1;
}

std::ostream & operator << (std::ostream & os, const commune & com)
{
    os << "Code/Nom : " << com.code << "\t" << com.nom << "\n"
       << "Status/Dcmax/Lienmax : " << com.status << "\t" << com.numdcmax << "\t" << com.lienmax << "\n"
       << "act/emp/sta/ent/sor" << "\t" << com.act << "\t" << com.emp << "\t" 
       << com.sta << "\t" << com.ent << "\t" << com.sor << "\n";
    return os ;
}
