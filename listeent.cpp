#include <cstdlib>
#include <vector>

#include "listeent.h"

//******************************************************************************
// Constructeur listeent
//******************************************************************************

listeent::listeent (int w_nbint, int w_nbcom):
nbcom (w_nbcom),indent (0)
{
    tete = new ent *[nbcom];
    vent = new ent  [w_nbint];

    for (unsigned int i = 0; i < nbcom; i++) {
        tete[i] = 0;
    }
}

listeent::~listeent ()
{
    delete[] tete;
    delete[] vent;  
}

//******************************************************************************
// Fonctions élémentaires
//******************************************************************************

ent *
listeent::ajoute_ent (int numdc, ent * pins, ent * ppos)
{
// ajoute le int pointé par pins en queue
// après le int pointé par ppos
// si ppos = 0, l'insertion se fait en tête
  if (ppos == 0)		// insertion en tête
    tete[numdc] = pins;
  else				// insertion après ppos
    ppos->next = pins;
  return pins;
}

ent *
listeent::insere_ent (int numdc, ent * pins, ent * pp,
			  ent * p)
{
// ajoute le int pointé par pins entre pp et p
// si pp = 0, l'insertion se fait en tête

  ajoute_ent ( numdc , pins , pp );
  pins->next = p;				  // fait le lien vers l'avant
  return pins;
}

ent *
listeent::delete_ent (int numdc, ent * p, ent * pp)
{
    // detruit le int pointé par p
    // nécessite le pointeur précédent pp pour lier la liste
    // si pp = 0, on détruit le premier int en modifiant la tête de liste

    if (p != 0) {
        if (pp == 0) {
            tete[numdc] = p->next;
        } else {
            pp->next = p->next;
        }
    }
    return p;
}

//******************************************************************************
// Insertion d'un ent
//******************************************************************************

ent *
listeent::insert (int numdc , int numdcins)
{
    // insere le int numdcins
    // dans le liste de numdc
    int i = renvoie_indent ();
    vent[i].numdc = numdcins ;
    insert_p (numdc, &vent[i]);
    return &vent[i] ;
}

int
listeent::insert_p (int numdc, ent * pent)
{
    // insere le int pointé par pint
    // dans le liste de numdc
    ent *p;
    ent *pp;

    bool insert_fait = false;

    for (p = tete[numdc], pp = 0; p != 0; pp = p, p = p->next) {
        if (p->numdc < pent->numdc) {
            // insertion au milieu entre pp et p, soit après pp
            insere_ent (numdc, pent, pp, p);
            insert_fait = true;
            break;
        }
    }

    if (insert_fait == false)
        // insertion en queue
        insere_ent (numdc, pent, pp, 0);
    return 0;
}


//******************************************************************************
// Merge les int
//******************************************************************************

void
listeent::merge (int numdca, int numdcb)
{
    //std::cout << "Merge : " << numdca << " " << numdcb << std::endl ;    
    ent *p = 0;			// pointeur sur la liste en cours de constitution
    ent *pa = tete[numdca];	// pointeur de la liste numdca
    ent *pb = tete[numdcb];	// pointeur de la liste numdcb

    // tant que les deux listes ne sont pas épuisées 
    while (pa != 0 || pb != 0) {	
        // on prend dans la liste A
        if ((pa != 0) && (pb == 0 || pa->numdc > pb->numdc)) {
            p = ajoute_ent (numdca, pa, p);
            pa = pa->next;
        } else if ((pb != 0) && (pa == 0 || pa->numdc < pb->numdc)) {
            // on prend dans la liste B
            p = ajoute_ent (numdca, pb, p);
            pb = pb->next;
        } else {
            // on cumule les int venant de B avec celui de A
            p = ajoute_ent (numdca, pa, p);
            pa = pa->next;
            pb = pb->next;
        }
        p->next = 0;
    }
    tete[numdcb] = 0;
}

void listeent::efface (int numdc , int numdceff)
{
    //std::cout << "Efface : " << numdc << " " << numdceff << std::endl ;  
    for (ent * p = tete[numdc] , *pp = 0;
            p != 0 && p->numdc >= numdceff ;
            pp = p , p = p->next ) {
        if (p->numdc == numdceff) {
            delete_ent ( numdc , p , pp ) ;
        }
    }
}

void
listeent::print (int numdc)
{
    if (tete[numdc] != 0) {
        for (ent * p = tete[numdc] ; p != 0 ; p = p->next) {
            std::cout << *p << "\n";
        }
    }
}

void
listeent::remplace (int numdc, int numdca , int numdcb)
{
    // cumule les ent vers dca et dcb
    // on sait déjà qu'il y a des ent vers dcb

    //std::cout << "Cumul : " << numdc << " " << numdca << " " << numdcb << std::endl ;

    ent *pa = 0;
    ent *pb = 0;
    ent *ppb = 0;

    int mindc = numdca < numdcb ? numdca : numdcb ;

    for (ent * p = tete[numdc], *pp = 0;
            p != 0 && p->numdc >= mindc;
            pp = p, p = p->next) {
        if (p->numdc == numdcb) {
            pb = p;
            ppb = pp;
        }
        if (p->numdc == numdca) {
            pa = p;
        }
    }
    delete_ent (numdc, pb, ppb);
    // numdca n'est pas dans liste ent
    if (pa == 0) {
        pb->numdc = numdca ;
        insert_p(numdc , pb );
    }
}
