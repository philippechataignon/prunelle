#ifndef MATFLUX_H
#define MATFLUX_H

#include <vector>

#include "valeur.h" 
#include "element.h" 
#include "commune.h" 

// typedef std::set<int> listent ;
// typedef std::set<int>::iterator listent_iter ;

class matflux
{
public:
    //******************************************************************************
    // Constructeur / Desctructeur
    //******************************************************************************

    matflux (int w_dim,int w_nbval);
    ~matflux ();

    void set_val (int w_lig,int w_col, int w_val);
    int get_val (int w_lig,int w_col);
    int get_dim()   {return dim;}
    int get_nbval() {return nbval;}
    //    listent list_num_lig(int w_lig) ;
    void affiche() ;
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
