#ifndef LIENS_H
#define LIENS_H

#include <vector>
#include "commune.h"
#include "matflux.h"
#include "lien.h"

class lien_aa : public lien 
{
public:
    lien_aa(matflux & w_mflux, std::vector<commune> & w_vcom) : lien(w_mflux, w_vcom) {}

    double calcul_elem(int numdc_l, int numdc_c, int nb, int nb_d);
    double val_stop() const {return 0.01;}
    double val_init() const {return -1;}
    bool is_sym() const {return 0;}
}
;

class lien_es : public lien 
{
public:
    lien_es(matflux & w_mflux, std::vector<commune> & w_vcom) : lien(w_mflux, w_vcom) {}

    double calcul_elem(int numdc_l, int numdc_c, int nb, int nb_d);
    double val_stop() const {return 0.0;}
    double val_init() const {return -1;}
    bool is_sym() const {return 1;}
}
;

class lien_sta : public lien 
{
public:
    lien_sta(matflux & w_mflux, std::vector<commune> & w_vcom) : lien(w_mflux, w_vcom) {}

    double calcul_elem(int numdc_l, int numdc_c, int nb, int nb_d);
    double val_stop() const {return 0.0;}
    double val_init() const {return -200;}
    bool is_sym() const {return 1;}
}
;

class lien_phc : public lien 
{
public:
    lien_phc(matflux & w_mflux, std::vector<commune> & w_vcom) : lien(w_mflux, w_vcom) {}

    double calcul_elem(int numdc_l, int numdc_c, int nb, int nb_d);
    double val_stop() const {return -1 ;}
    double val_init() const {return -1 ;}
    bool is_sym() const {return 0;}
}
;
#endif
