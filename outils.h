#include "flux.h"

class double_flux
{
public:
    flux * p;
    flux * pp;
    double_flux (flux * w_p = 0 , flux * w_pp = 0) : p(w_p),pp(w_pp) {}
}
;

