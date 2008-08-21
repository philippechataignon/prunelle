#include <iostream>
#include "matflux.h"
#include "valeur.h"

//******************************************************************************
// Constructeur matflux
//******************************************************************************

matflux::matflux (int w_dim, int w_nbval):
dim(w_dim),nbval(w_nbval),indlig(0),indcol(0),indval(0)
{
    // tableau des valeurs
    tabval = new valeur[nbval] ;
    // tete de ligne = pointeur sur 1er élément
    tete_l = new element*[dim] ;
    // les éléments des lignes 
    elt_l  = new element[nbval] ;
    // tete de colonne = pointeur sur 1er élément
    tete_c = new element*[dim] ;
    // les éléments des colonnes
    elt_c  = new element[nbval] ;

    for (unsigned int i = 0; i < dim; i++) {
        tete_l[i] = 0 ;
        tete_c[i] = 0 ;
    }
}

matflux::~matflux ()
{
    delete[] tabval ;
    delete[] tete_l ;
    delete[] elt_l  ;
    delete[] tete_c ;
    delete[] elt_c  ;
}

void matflux::set_val (int w_lig,int w_col, int w_val)
{
    int i_val = indval++ ;
    int i_lig = indlig++ ;
    int i_col = indcol++ ;
    tabval[i_val].nb  = w_val ;
    elt_l[i_lig]=element(w_col,i_val) ;
    insert(tete_l,w_lig,&elt_l[i_lig]) ;
    elt_c[i_col]=element(w_lig,i_val) ;
    insert(tete_c,w_col,&elt_c[i_col]) ;
}

valeur matflux::get_val (int w_lig,int w_col) 
{
    for (element* i=tete_l[w_lig]; i !=0 && i->numlc >= w_col; i=i->next) {
        if (i->numlc == w_col) {
            return tabval[i->numval] ;
        }
    }
    return valeur() ; 
}

void matflux::affiche()
{
    std::cout << "Tabval " ;
    for (unsigned int i=0 ; i<indval ; i++) {
         std::cout << i << ":"<< tabval[i] << ","  ;
        }
    std::cout << std::endl ;
    for (unsigned int i=0 ; i<dim ; i++) {
        std::cout << "Lig " << i << " : " ;
        for (element* j=tete_l[i] ; j != 0 ; j=j->next) {
             std::cout << *j <<  "|"  ;
        }
        std::cout << std::endl ;
    }
    for (unsigned int i=0 ; i<dim ; i++) {
        std::cout << "Col " << i << " : " ;
        for (element* j=tete_c[i] ; j != 0 ; j=j->next) {
             std::cout << *j << "|"  ;
        }
        std::cout << std::endl ;
    }
}

void matflux::affiche_mat()
{
    std::cout << std::endl ;
    for (unsigned int i=0 ; i<dim ; i++) {
        for (unsigned int j=0 ; j<dim ; j++) {
            std::cout << get_val(i,j) << "|" ;
            }
        std::cout << std::endl ;
    }
}

void matflux::merge (int inda, int indb)
{
    merge_lc(tete_l,tete_c,inda,indb) ;
    merge_lc(tete_c,tete_l,inda,indb) ;
}

//******************************************************************************
// Fonctions élémentaires
//******************************************************************************

element *
matflux::ajoute_element (element* vtete[], int ind, element* pins, element* pp)
{
    //std::cout << "Insère element : (H)" << vtete << "\t" << pins <<
    //    "\taprès" << pp << "\t" << std::endl;
    if (vtete[ind] == 0 || pp == 0) {		// insertion en tête
        vtete[ind] = pins;
    } else {				// insertion après ppos
        pp->next = pins;
    }
    return pins;
}

element *
matflux::insere_element (element* vtete[], int ind, element* pins, element* pp,
			  element* p)
{
    // ajoute element pointé par pins entre pp et p
    // si pp = 0, l'insertion se fait en tête

    //std::cout << "Insère element : (H)" << vtete << "\t" << pins <<
    //    "\taprès" << pp << "\tavant" << p << std::endl;

    ajoute_element(vtete,ind, pins, pp) ;
    pins->next = p;				  // fait le lien vers l'avant
    return pins;
}

element *
matflux::delete_element (element* vtete[], int ind, element* p, element* pp)
{
    // detruit element pointé par p
    // nécessite le pointeur précédent pp pour lier la liste
    // si pp = 0, on détruit le premier element en modifiant la tête de liste
    // std::cout << "Delete element : " << ind << "\t" << p << "\t" << pp <<  std::endl;

    if (p) {
        if (pp == 0) {
            vtete[ind] = p->next; 
        } else {
            pp->next = p->next;
        }
    }
    return p;
}

//******************************************************************************
// Fonctions d'insertion
//******************************************************************************

int
matflux::insert (element* vtete[], int ind, element* pins)
{
    // insere le element pointé par pins dans la ligne/colonne
    // numéro w_num
    element* p;
    element* pp;

    bool insert_fait = false;

    for (p = vtete[ind], pp = 0; p != 0; pp = p, p = p->next) {
        if (p->numlc <= pins->numlc) {
            if (p->numlc == pins->numlc) {
                std::cout << "Egalité indice" << ind << "/" << p->numlc << std::endl ;
                delete_element(vtete,ind,pp,p) ;
            }
            // insertion au milieu entre pp et p, soit après pp
            insere_element (vtete,ind, pins, pp, p);
            insert_fait = true;
            break;
        }
    }

    if (insert_fait == false) {
        // insertion en queue
        insere_element (vtete,ind, pins, pp, 0);
    }
    return 0;
}

void
matflux::merge_lc (element* vtete_l[], element* vtete_c[], int inda, int indb )
{
    element *p = 0;                 // pointeur sur la liste en cours de constitution
    element *pa = vtete_l[inda];    // pointeur de la liste numdca
    element *pb = vtete_l[indb];    // pointeur de la liste numdcb
    // tant que les deux listes ne sont pas épuisées
    while (pa != 0 || pb != 0) {
        if ((pa != 0) && (pb == 0 || pa->numlc > pb->numlc)) {
            // on prend dans la liste A : cas le plus simple
            p = ajoute_element (vtete_l, inda, pa, p);
            pa = pa->next;
        } else if ((pb != 0) && (pa == 0 ||pb->numlc > pa->numlc)) {
            // on prend dans la liste B : il faut faire le changement d'indice dans le dual
            p = ajoute_element (vtete_l, inda, pb, p);
            change_ind(vtete_c, pb->numlc, indb, inda) ;
            pb = pb->next;
        } else {
            // on cumule l'element venant de B avec celui de A : 
	    // on supprime dans le dual pour éviter les 0 inutiles 
            tabval[pa->numval].nb += tabval[pb->numval].nb;
            tabval[pb->numval].nb = 0 ;
            delete_ind(vtete_c, pb->numlc, indb) ;
            p = ajoute_element (vtete_l, inda, pa, p);
            pa = pa->next;
            pb = pb->next;
        }
        p->next = 0;
    }
    vtete_l[indb] = 0;
}
 
void
matflux::change_ind(element* vtete[], int ind, int indb, int inda)
{
    // Transforme indb en inda dans liste ind
    for (element *p = vtete[ind], *pp = 0; p != 0 && p->numlc >= indb ; pp = p, p = p->next) {
        if (p->numlc == indb) {
            p->numlc = inda ;
            delete_element(vtete,ind,p,pp)   ;
            insert(vtete,ind,p) ;
        }
    }
}

void
matflux::delete_ind(element* vtete[], int ind, int indb)
{
    // Supprime indb dans liste ind
    for (element *p = vtete[ind], *pp = 0; p != 0 && p->numlc >= indb ; pp = p, p = p->next) {
        if (p->numlc == indb) {
            delete_element(vtete,ind,p,pp)   ;
        }
    }
}
