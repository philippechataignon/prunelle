#ifndef matflux_h
#define matflux_h

#include <vector>
#include <set>
#include <iterator>
#include "valeur.h" 
#include "element.h" 

typedef std::set<element> ligcol   ;
typedef std::set<element>::iterator ligcol_iter   ;
typedef std::vector<valeur> tabval ;

class matflux
{
public:
    //******************************************************************************
    // Constructeur / Desctructeur
    //******************************************************************************

    matflux (int w_dim,int w_nbval);
    ~matflux ();

    int set_val (int w_lig,int w_col, int w_val);
    int get_val (int w_lig,int w_col);
    void imprime() ;
    
private:
    int nbval  ;
    int indval ;
    const unsigned int dim ;

    std::vector<ligcol> lig ; 
    std::vector<ligcol> col ;
    tabval val ;
}
;
#endif
