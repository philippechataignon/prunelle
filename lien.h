#ifndef LIEN_H
#define LIEN_H

#include <vector>

#include "commune.h"
#include "matflux.h"

class lien
{
public:
    lien(matflux & w_mflux, std::vector<commune> & w_vcom) : mflux(w_mflux), vcom(w_vcom) {}

    virtual double calcul_elem(int numdc_l, int numdc_c, int nb, int nb_d) = 0;
    virtual double val_init() const = 0;
    virtual double val_stop() const = 0;
    virtual bool is_sym() const = 0;
    
    void calcul_init() ;
    void calcul_sim(int numdc) ;
    void raz_calc(int numdc) ;
    
protected:
    void calcul_max(int numdc, double lien, int dcmaxlien);
    
    matflux & mflux ; 
    std::vector<commune> & vcom ;
}
;
#endif
