#ifndef LIEN_AA_H
#define LIEN_AA_H

#include <vector>
#include "commune.h"
#include "matflux.h"
#include "class_lien.h"

class lien_aa : public lien 
{
public:
    lien_aa(matflux & w_mflux, std::vector<commune> & w_vcom) : lien(w_mflux, w_vcom) {}

    float calcul_elem(int numdc_l, int numdc_c, int nb, int nb_d);
    float val_stop() const {return 0.01;}
    float val_init() const {return -1;}
}
;
#endif
