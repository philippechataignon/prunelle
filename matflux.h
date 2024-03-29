#ifndef MATFLUX_H
#define MATFLUX_H

#include <vector>

#include "valeur.h" 
#include "element.h" 
#include "commune.h" 

class matflux
{
public:
    //******************************************************************************
    // Constructeur / Desctructeur
    //******************************************************************************

    matflux (int w_dim,int w_nbval);
    ~matflux ();

    void set_val (int w_lig,int w_col, double w_val);
    valeur get_val (int w_lig,int w_col);
    int get_dim()   {return dim;}
    int get_nbval() {return nbval;}

    void affiche() ;
    void affiche_mat() ;
    void merge (int inda, int indb) ;
    
    friend class lien ;
private:
    element* ajoute_element (element* vtete[], int ind, element* pins, element* pp) ;
    element* insere_element (element* vtete[], int ind, element* pins, element* pp, element* p) ;
    element* delete_element (element* vtete[], int ind, element* p, element* pp) ;
    int insert    (element* vtete[], int ind, element* pelement) ;
    void merge_lc (element* vtete[], element* vtete_c[], int inda, int indb ) ;
    void change_ind(element* vtete[], int ind, int indb, int inda) ;
    void delete_ind(element* vtete[], int ind, int indb) ;
    
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
