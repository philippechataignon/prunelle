#include <iostream>
#include <iterator>

#include "matflux.h"
#include "valeur.h"

//******************************************************************************
// Constructeur matflux
//******************************************************************************

matflux::matflux (int w_dim, int w_nbval):
dim(w_dim),nbval(w_nbval),indval(0)
{
    val.reserve(nbval) ;
    lig.reserve(dim)   ;
    col.reserve(dim)   ;
    val = tabval (nbval) ;
    lig = std::vector< ligcol > (dim) ;
    col = std::vector< ligcol > (dim) ;
}

matflux::~matflux ()
{
}

int matflux::set_val (int w_lig,int w_col, int w_val)
{
    int ind = indval++ ;
    val[ind].nb  = w_val ;
    lig[w_lig].insert(element(w_col,ind)) ;
    col[w_col].insert(element(w_lig,ind)) ;
}

int matflux::get_val (int w_lig,int w_col) 
{
    int ret_val = 0 ;
    ligcol_iter l ;
    l = lig[w_lig].find(element(w_col,0)) ;
    if (l != lig[w_lig].end() ) {
        ret_val=val[l->numval].nb ;
    } else {
        ret_val = 0 ;
    }
    return ret_val ;
}

void matflux::imprime ()
{
    for (int i=0 ; i<dim ; i++) {
        std::cout << "Ligne " << i << " : " ;
        for (ligcol_iter j=lig[i].begin() ; j != lig[i].end() ; ++j) {
            std::cout << *j << "[" << val[j->numval] << "] | "  ;
        }
        std::cout << std::endl ;
    }
    for (int i=0 ; i<dim ; i++) {
        std::cout << "Col " << i << " : " ;
        for (ligcol_iter j=col[i].begin() ; j != col[i].end() ; ++j) {
            std::cout << *j << "[" << val[j->numval] << "] | "  ;
        }
        std::cout << std::endl ;
    }
}
