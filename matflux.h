#ifndef matflux_h
#define matflux_h

#include "valeur.h" 
#include "element.h" 

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
    void merge (int inda, int indb) ;
    
private:
    element* ajoute_element (element* vtete[], int ind, element* pins, element* pp) ;
    element* insere_element (element* vtete[], int ind, element* pins, element* pp, element* p) ;
    element* delete_element (element* vtete[], int ind, element* p, element* pp) ;
    int insert    (element* vtete[], int ind, element* pelement) ;
    void merge_lc (element* vtete[], int inda, int indb ) ;
    
    const unsigned int dim ;
    int nbval  ;
    int indlig ;
    int indcol ;
    int indval ;

    element*  elt_l  ;
    element** tete_l ;
    element*  elt_c  ;
    element** tete_c ;
    valeur*   tabval ;
}
;
#endif
