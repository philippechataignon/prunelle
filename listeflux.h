#ifndef listeflux_h
#define listeflux_h
#include <vector>
#include "flux.h"
#include "commune.h"
#include "listeent.h"
#include "outils.h"

class listeflux
{
public:
    //******************************************************************************
    // Constructeur / Desctructeur
    //******************************************************************************

    listeflux (int w_nbflux,int w_nbcom);
    ~listeflux ();

    //******************************************************************************
    // Fonctions élémentaires
    //******************************************************************************

    flux *delete_flux (int numdc, flux * p, flux * pp);
    void  delete_flux (int numdc, double_flux df);  
    flux *ajoute_flux (int numdc, flux * pins, flux * ppos);
    flux *insere_flux (int numdc, flux * pins, flux * pp, flux * p);

    //******************************************************************************
    // Fonctions d'insertion
    //******************************************************************************

    int insert (int numdc, int indflux);
    int insert (int numdc, flux * indflux);
    void ajoute_flux_init (std::vector < commune > &vcom , listeent & lent , int numdcr, int numdclt, int nb);

    //******************************************************************************
    // Calcul des liens
    //******************************************************************************

    float calcul_lien (std::vector < commune > &vcom, int numdcr , flux * p , int type );
    void calcul_lien (std::vector < commune > &vcom, int numdc , int type );
    void calcul_lien (std::vector < commune > &vcom, int type );

    //******************************************************************************
    // Fonctions d'agrégation
    //******************************************************************************

    void agrege (std::vector < commune > &vcom , listeent & lent , int numdca, int numdcb , int type);
    void merge_flux (std::vector < commune > &vcom , int numdca, int numdcb , int type );
    void cumul (int numdc, int numdca , int numdcb);

    flux * max_lien (int numdc);
    void maj_max (std::vector < commune > &vcom) ;
    void test_max_lien (int numdc , flux * p);

    void print ();
    void print (int numdc);
    int rech_flux (int numdca , int numdcb);
    double_flux pp_rech_flux (int numdca , int numdcb);
    int renvoie_indflux () { return indflux++ ; }


private:
    flux* p_rech_flux (int numdca , int numdcb );

    int indflux;
    const unsigned int nbcom;
    int maxcom;

    flux **tete;		// tableau des pointeurs sur flux lignes/colonnes
    flux **maxp;		// tableau des pointeurs sur le flux maximum en ligne
    bool  *maxflag;		// 
    flux *vflux;		// tableau des flux
}
;
#endif
