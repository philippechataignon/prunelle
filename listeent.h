//---------------------------------------------------------------------------
#ifndef listeentH
#define listeentH

#include "ent.h"

class listeent
{
public:
//******************************************************************************
// Constructeur / Desctructeur
//******************************************************************************

  listeent (int w_nbent,int w_nbcom);
  ~listeent();
   
  ent * insert (int numdc , int numdcins);
  void efface (int numdc , int numdceff) ;
  void merge  (int numdca , int numdcb ) ;
  void print (int numdc)  ;
  
  friend class listeflux;
  
private:
//******************************************************************************
// Fonctions élémentaires
//******************************************************************************

  ent* delete_ent (int numdc, ent * p, ent * pp);
  ent* ajoute_ent (int numdc, ent * pins, ent * ppos);
  ent* insere_ent (int numdc, ent * pins, ent * pp, ent * p);

//******************************************************************************
// Fonctions d'insertion
//******************************************************************************

  int insert_p (int numdc, ent * indent);

//******************************************************************************
// Fonctions d'agrégation
//******************************************************************************

  int renvoie_indent () { return indent++ ; }
  void remplace (int numdc, int numdca , int numdcb);


private:
  int indent;
  const unsigned int nbcom;
  
  ent **tete;		// tableau des pointeurs sur int lignes/colonnes
  ent *vent;		// tableau des ent
} ;
//---------------------------------------------------------------------------
#endif
