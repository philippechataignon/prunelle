//---------------------------------------------------------------------------
#include <iostream>
#pragma hdrstop

#include <cstdlib>
#include <vector>
#include "listeflux.h"


//******************************************************************************
// Constructeur listeflux
//******************************************************************************

listeflux::listeflux (int w_nbflux, int w_nbcom):
nbcom (w_nbcom),maxcom(0),indflux (0)
{
  tete = new flux *[nbcom];
  maxflag = new bool [nbcom];
  maxp = new flux *[nbcom];
  vflux = new flux[w_nbflux];

  for (unsigned int i = 0; i < nbcom; i++)
    {
      tete[i] = 0;
      maxflag[i] = false;
      maxp[i] = 0;
    }
}

listeflux::~listeflux ()
{
  delete[] vflux;
  delete[] tete;
  delete[] maxp;
  delete[] maxflag;
}

//******************************************************************************
// Fonctions élémentaires
//******************************************************************************

flux *
listeflux::ajoute_flux (int numdc, flux * pins, flux * ppos)
{
// ajoute le flux pointé par pins en queue
// après le flux pointé par ppos
// si ppos = 0, l'insertion se fait en tête
  if (ppos == 0)		// insertion en tête
    tete[numdc] = pins;
  else				// insertion après ppos
    ppos->next = pins;
  return pins;
}

flux *
listeflux::insere_flux (int numdc, flux * pins, flux * pp,
			  flux * p)
{
// ajoute le flux pointé par pins entre pp et p
// si pp = 0, l'insertion se fait en tête

//  std::cout << "Insère flux : " << numdc << "\t" << *pins <<
//    "\taprès" << *pp << "\tavant" << *p << std::endl;

  ajoute_flux (numdc, pins, pp);
  pins->next = p;				  // fait le lien vers l'avant
  return pins;
}

flux *
listeflux::delete_flux (int numdc, flux * p, flux * pp)
{
// detruit le flux pointé par p
// nécessite le pointeur précédent pp pour lier la liste
// si pp = 0, on détruit le premier flux en modifiant la tête de liste
//      std::cout << "Delete flux : " << numdc << "\t" << *p <<
//         "\tprécédent" << *pp <<  std::endl;

if (p != 0)
{
  if (pp == 0)
    tete[numdc] = p->next;
  else
  {
    pp->next = p->next;
  }
}
return p;
}

void
listeflux::delete_flux (int numdc, double_flux df)
{
    if ( df.p != 0 )
        delete_flux(numdc , df.p , df.pp );
}

int
listeflux::rech_flux (int numdca , int numdcb)
{
  flux * p = p_rech_flux(numdca,numdcb) ;
  if (p  == 0)
      return 0;
  else
      return p->nb ;
}

flux*
listeflux::p_rech_flux (int numdca , int numdcb)
{
  for (flux * p = tete[numdca];
       p != 0 && p->numdclt >= numdcb ;
       p = p->next )
  {
    if (p->numdclt == numdcb)
        return p ;
  }
  return 0;
}

double_flux
listeflux::pp_rech_flux (int numdca , int numdcb)
{
  for (flux * p = tete[numdca] , *pp = 0;
       p != 0 && p->numdclt >= numdcb ;
       pp = p , p = p->next )
  {
    if (p->numdclt == numdcb)
        return double_flux(p,pp);
  }
  return double_flux(0,0);
}



//******************************************************************************
// Insertion d'un flux
//******************************************************************************


void
listeflux::ajoute_flux_init (std::vector < commune > &vcom , listeent & lent , int numdcr, int numdclt, int nb)
{
  //std::cout << numdcr << "\t" << numdclt << "\t" << nb << std::endl ;
  if (numdcr != numdclt)
  {
    int indflux = renvoie_indflux ();
    vflux[indflux].numdclt = numdclt;
    vflux[indflux].nb = nb;
    insert (numdcr, indflux);
 	//vcom[numdclt].ajoute_coment(numdcr);
 	lent.insert(numdclt , numdcr) ;
  	vcom[numdcr].sor += nb;
  	vcom[numdcr].act += nb;
  	vcom[numdclt].ent += nb;
  	vcom[numdclt].emp += nb;
  }
  else
  {
  	vcom[numdcr].sta += nb;
  	vcom[numdcr].act += nb;
  	vcom[numdcr].emp += nb;
  }
}


//******************************************************************************
// Fonctions d'insertion
//******************************************************************************


int
listeflux::insert (int numdc, int indflux)
{
// insere le flux numéro w_indflux dans la ligne/colonne (selon irlt)
// numéro w_numdc
  flux *pflux = &vflux[indflux];
  insert (numdc, pflux);
  return 0;
}

int
listeflux::insert (int numdc, flux * pflux)
{
// insere le flux pointé par pflux dans la ligne/colonne (selon irlt)
// numéro w_numdc
  flux *p;
  flux *pp;

  bool insert_fait = false;

  for (p = tete[numdc], pp = 0; p != 0; pp = p, p = p->next)
    {
      if (p->numdclt < pflux->numdclt)
      {
		// insertion au milieu entre pp et p, soit après pp
		insere_flux (numdc, pflux, pp, p);
        insert_fait = true;
        break;
      }
    }

  if (insert_fait == false)
    // insertion en queue
    insere_flux (numdc, pflux, pp, 0);
  return 0;
}

void
listeflux::print ()
{
  std::cout << "Liste flux :\n";
  for (unsigned int i = 0; i < nbcom; i++)
    print(i);
}

void
listeflux::print (int numdc)
{
  if (tete[numdc] != 0)
    {
      std::cout << numdc << "\t" << tete[numdc] << "\n";
      for (flux * p = tete[numdc]; p != 0; p = p->next)
        std::cout << *p << "\n";
    }
}


//******************************************************************************
// Calcul des liens
//******************************************************************************

float
listeflux::calcul_lien (std::vector < commune > &vcom, int numdcr , flux * p , int type )
{
// calcul du lien élémentaire
  int numdclt = p->numdclt ;
  switch (type)
  {
  case 0 :
  //lien standard
    {
    int act0 = vcom[numdcr].act;
    if ( act0 !=0 )
        p->lien = static_cast<float> (p->nb) / act0 * 100;
    else
        p->lien = 0;
    break;
    }
  case 1 :
    {
  // lien échanges
    int act0 = vcom[numdcr].act;  
    int act1 = vcom[numdclt].act;
    if ( (act0 + act1) != 0)
    {
      int nb1 = rech_flux (numdclt , numdcr);
      p->lien = static_cast < float >(p->nb + nb1) / ( act0 + act1 ) * 100;
      //std::cout << numdcr << " " << numdclt << " " << p->nb << " " << nb1 << std::endl ;
    }
    else
      p->lien = 0;
    break;  
    }
  case 2 :
  //lien sortants
    {
    int sor0 = vcom[numdcr].sor;
    if ( sor0 !=0 )
        p->lien = static_cast<float> (p->nb) / sor0 * 100;
    else
        p->lien = 0;
    break;
    }
  default:
    {
        p->lien = 0 ;
        break;
    }
  }
  return p->lien;
}

void
listeflux::calcul_lien (std::vector < commune > &vcom, int numdc, int type)
{
// calcul des liens d'une commune
  for (flux * p = tete[numdc]; p != 0; p = p->next)
    calcul_lien (vcom, numdc , p , type);
}


void
listeflux::calcul_lien (std::vector < commune > &vcom , int type )
{
// calcul de tous les liens de la liste
  for (unsigned int i = 0; i < nbcom ; i++)
    {
      if (vcom[i].status == 1)
        calcul_lien (vcom, i , type);
    }
}

//******************************************************************************
// Agrégation
//******************************************************************************

void
listeflux::agrege (std::vector < commune > &vcom , listeent & lent ,  int numdca, int numdcb , int type)
{
  double_flux dfab = pp_rech_flux ( numdca , numdcb) ;
  double_flux dfba = pp_rech_flux ( numdcb , numdca) ;  
  
  int nab = dfab.p == 0 ? 0 : dfab.p->nb ;
  int nba = dfba.p == 0 ? 0 : dfba.p->nb ;

  vcom[numdca].sta += vcom[numdcb].sta + nab + nba ;
  vcom[numdca].ent += (vcom[numdcb].ent - nab - nba) ;
  vcom[numdca].sor += (vcom[numdcb].sor - nab - nba) ;
  vcom[numdca].emp = vcom[numdca].sta + vcom[numdca].ent;
  vcom[numdca].act = vcom[numdca].sta + vcom[numdca].sor;
 
  delete_flux (numdca , dfab ) ;
  delete_flux (numdcb , dfba ) ;
  
  for (flux * p = tete[numdcb]; p != 0 ; p = p->next)
  {
    if (p->numdclt != numdca && p->numdclt != numdcb)
        lent.remplace( p->numdclt , numdca , numdcb );
  }
  
  merge_flux (vcom , numdca, numdcb ,type);		// on merge les flux sortants de A et B

  for (ent * pe = lent.tete[numdcb] ; pe != 0 ; pe = pe->next)
  {
    if (pe->numdc != numdca && pe->numdc != numdcb )
        cumul ( pe->numdc , numdca , numdcb );
  }


  lent.merge (numdca, numdcb) ;
  lent.efface (numdca , numdcb );
  lent.efface (numdca , numdca ) ;
  
  /*delete_flux (numdca , dfab ) ;
  delete_flux (numdcb , dfba ) ;

  for (flux * p = tete[numdcb]; p != 0 ; p = p->next)
    lent.efface( p->numdclt ,  numdcb );  
  
  merge_flux (vcom , numdca, numdcb ,type);		// on merge les flux sortants de A et B

  
  for (ent * pe = lent.tete[numdcb] ; pe != 0 ; pe = pe->next)
        cumul ( pe->numdc , numdca , numdcb );
  lent.merge (numdca, numdcb) ;
  lent.efface (numdca , numdcb );*/
    
  for (ent * pe = lent.tete[numdca] ; pe != 0 ; pe = pe->next)
  {
    
    flux * p = p_rech_flux(pe->numdc , numdca);
    
    if (p==0)
    {
        std::cout << "Erreur : pointeur nul dans agrege" ;
        std::exit (1);
    }
    calcul_lien (vcom, pe->numdc , p , type);
    int dcmax = maxp[pe->numdc]->numdclt ;
    if ( dcmax == numdca || dcmax == numdcb )
    {
        maxp[pe->numdc] = 0;
        maxflag[pe->numdc] = false ;
    }
    else
    {
        test_max_lien (pe->numdc , p);
    }
  }

  maxp[numdca] = 0;
  maxflag[numdca] = false;

  vcom[numdcb].status = 0 ;
  maxp[numdcb] = 0;
  maxflag[numdcb] = true;
  maj_max (vcom) ;
}

//******************************************************************************
// Merge les flux
//******************************************************************************

void
listeflux::merge_flux (std::vector < commune > &vcom , int numdca, int numdcb , int type )
{
  flux *p = 0;			// pointeur sur la liste en cours de constitution
  flux *pa = tete[numdca];	// pointeur de la liste numdca
  flux *pb = tete[numdcb];	// pointeur de la liste numdcb

  while (pa != 0 || pb != 0)	// tant que les deux listes ne sont pas épuisées
    {
    	// on prend dans la liste A
        if ((pa != 0) && (pb == 0 || pa->numdclt > pb->numdclt))
    	{
            p = ajoute_flux (numdca, pa, p);
            pa = pa->next;
    	}
        else
    	if ((pb != 0) && (pa == 0 || pa->numdclt < pb->numdclt))
    	{
    	  // on prend dans la liste B
            p = ajoute_flux (numdca, pb, p);
            pb = pb->next;
    	}
        else
    	{
    	  // on cumule les flux venant de B avec celui de A
            pa->nb += pb->nb;
            p = ajoute_flux (numdca, pa, p);
            calcul_lien (vcom , numdca , p , type );
            pa = pa->next;
            pb = pb->next;
        }
    p->next = 0;
    }
  tete[numdcb] = 0;
}

void
listeflux::cumul (int numdc, int numdca , int numdcb)
{
// cumule les flux vers dca et dcb
// on sait déjà qu'il y a des flux vers dcb

//std::cout << "Cumul : " << numdc << " " << numdca << " " << numdcb << std::endl ;

  flux *pa = 0;
  flux *pb = 0;
  flux *ppb = 0;

  int mindc = numdca < numdcb ? numdca : numdcb ;

  for (flux * p = tete[numdc], *pp = 0;
       p != 0 && p->numdclt >= mindc;
       pp = p, p = p->next)
    {
      if (p->numdclt == numdcb)
	{
	  pb = p;
	  ppb = pp;
	}
      if (p->numdclt == numdca)
	{
	  pa = p;
	}
}

//  std::cout << *pa << "\n" << *pb << "\n" ;

  if (pb == 0)
  {
  	std::cout <<  "Erreur : pb pointeur nul dans listeflux::cumul" << std::endl ;
  	std::exit(0);
  }

  if (pa != 0)			//il y a des flux vers numdca
    {
   	  pa->nb += pb->nb;
      delete_flux (numdc, pb, ppb);
    }
  else
    {
      //std::cout << "Cumul sans flux vers " << numdca << "\n" ;
      delete_flux (numdc, pb, ppb);
      pb->numdclt = numdca ;
      insert(numdc , pb );
    }
}

//******************************************************************************
// Détermination du maximum
//******************************************************************************

flux *
listeflux::max_lien (int numdc)
{
  if ( maxflag[numdc] == false )
    {
      for (flux * p = tete[numdc]; p != 0; p = p->next)
        test_max_lien (numdc , p);
      maxflag[numdc] = true ;
    }
  return  maxp[numdc] ;
}

void listeflux::maj_max (std::vector < commune > &vcom)
{
  for (unsigned int i=0 ; i<vcom.size() ; i++)
  {
    if ( vcom[i].status == 1)
  	{
  	    flux * mp = max_lien(i);
  	    if (mp != 0)
  	    {
  	      vcom[i].numdcmax = mp->numdclt ;
  	      vcom[i].lienmax = mp->lien ;
  	    }
  	    else
  	    {
  	      vcom[i].numdcmax = -1 ;
  	      vcom[i].lienmax = 0 ;
  	    }
 	}
 	else
    {
      vcom[i].numdcmax = -1 ;
      vcom[i].lienmax = 0 ;
    }
  }
}

void listeflux::test_max_lien (int numdc , flux * p)
{
    flux * mp = maxp[numdc];
    if (mp == 0 || p->lien > mp->lien || ( mp->lien == p->lien && p->nb < mp->nb ))
    {
        // on a un nouveau maximum
 	    maxp[numdc] = p;
 	}
}
