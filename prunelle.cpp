#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cmath>

#include "flux.h"
#include "listeflux.h"
#include "listeent.h"
#include "commune.h"
#include "prunelle.h"

int main(int argc, char* argv[])
{
    std::cout << "Prunelle V 7.01 - " << __DATE__ << " - " << __TIME__ <<
        std::endl;

    if (argc != 5 && argc != 6) {
        std::cout << "Entrer fichier couple, fichier nom,fichier sortie et type de lien\n";
        std::cout << "Types de lien :\n";
        std::cout << "0 : flux(A,B)/act(A)\n1 : (flux(A,B)+flux(B,A)/act(A)+act(B))\n2 : flux(A,B)/sor(A)\n" ;
        std::exit (0);
    }

    std::ifstream flu (argv[1]);
    if (flu == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier couple" << std::endl ;
        exit(1);
    }

    std::ifstream com (argv[2]);
    if (com == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier des noms" << std::endl ;
        exit(1);
    }

    std::ofstream out (argv[3]);
    if (out == 0) {
        std::cout << "Erreur : impossible d'ouvrir le fichier sortie" << std::endl ;
        exit(1);
    }

    std::vector < commune > vcom;
    lecture_commune (vcom , com) ;

    int nbmaxflux ;
    flu >> nbmaxflux ;

    listeflux lflux (nbmaxflux , vcom.size());
    listeent  lent  (nbmaxflux , vcom.size());

    lecture_flux (vcom, lflux , lent , flu);

    const int type = std::atoi(argv[4]) ;
    lflux.calcul_lien (vcom , type);  //calcul tous les liens
    lflux.maj_max (vcom) ;

    bool fin ;
    unsigned int ii = 1 ;

    do {
        if (argv[5] != 0 && argv[5] == std::string("-p"))
            affiche(vcom , lflux , lent);

        float maxlien = 0 ;
        int maxdcr = -1 ;
        int maxdclt = -1 ;

        for (unsigned int i=0 ; i<vcom.size() ; i++) {
            if (vcom[i].status == 1) {
                // si on a un nouveau maximum
                if (vcom[i].lienmax > maxlien ||  
                    ( std::fabs (maxlien - vcom[i].lienmax ) < 1E-3 
                    && vcom[i].act > vcom[maxdcr].act) ) {
                    maxdcr = i;
                    maxdclt = vcom[i].numdcmax ;
                    maxlien = vcom[i].lienmax ;
                }
            }  
        }

        fin = (maxdcr == -1 || maxdclt == -1 || maxlien < 1E-5 || ii >= vcom.size()) ;  


        if (!fin) {
            if (std::fabs (vcom[maxdcr].lienmax - vcom[maxdclt].lienmax ) < 1E-2 && vcom[maxdclt].act < vcom[maxdcr].act) {
                int tmp=maxdclt ;
                maxdclt =maxdcr ;
                maxdcr = tmp;
                std::cout << "*";
            }
            std::cout << ">>> Agrégation n° " << ii << "\t" << maxdclt << "\t" << vcom[maxdclt].nom 
                      << " < " << maxdcr << " " << vcom[maxdcr].nom << " = " << maxlien << std::endl ;
            out << ii << "\t" << maxdclt << "\t" << maxdcr << "\t" << maxlien << "\n" ;
            lflux.agrege(vcom , lent , maxdclt , maxdcr , type );
            //affiche(vcom,lflux,lent);
            ii++;
        }
    }
    while (!fin);
    return 0;
}

void affiche(std::vector<commune> & vcom , listeflux & lflux , listeent & lent)
{
    for (unsigned int numdc = 0 ; numdc < vcom.size() ; numdc++)
        affiche(vcom,lflux,lent,numdc);

}

void affiche(std::vector<commune> & vcom ,listeflux & lflux , listeent & lent ,int numdc)
{
    std::cout << "--- Commune " << numdc<< "\t" << vcom[numdc] ;
    lflux.print(numdc);
    lent.print(numdc);
    std::cout << "---<<< " << std::endl ;
}

void lecture_commune(std::vector<commune> & vcom , std::ifstream & com)
{
    std::cout << "Début lecture fichier nom des communes" << std::endl;
    while (com) {
        std::string code;
        std::string nom;
        com >> code;
        com >> std::ws >> nom;

        if (!code.empty ())
            vcom.push_back (commune (code, nom));
    }
    std::cout << "Fin lecture fichier nom des communes" << std::endl;
}

  
void lecture_flux (std::vector<commune> & vcom , listeflux & lflux , listeent & lent , std::ifstream & flu)
{
    std::cout << "\nDébut lecture fichier flux" << std::endl ;
    unsigned int ii=0 ;
    while (flu) {
        std::string coder;
        std::string codelt;
        int nb;

        typedef std::vector < commune >::iterator viter ;
        typedef std::pair<viter,viter> piter ;

        flu >> coder >> codelt >> nb;

        if (!coder.empty ()) {
            piter icomr = std::equal_range (vcom.begin (), vcom.end (), commune (coder));
            if (icomr.first == icomr.second) {
                std::cout << "Commune de résidence non trouvée : " << coder << "\n";
            } else {  
                piter icomlt = std::equal_range (vcom.begin (), vcom.end (), commune (codelt));
                if (icomlt.first == icomlt.second) {
                    std::cout << "Commune de lieu de travail non trouvée : " << codelt << "\n";
                } else {
                    int numdcr = std::distance (vcom.begin (), icomr.first) ;
                    int numdclt = std::distance (vcom.begin (), icomlt.first) ;
                    lflux.ajoute_flux_init (vcom , lent , numdcr, numdclt , nb); 
                }
            }

            if ( ii % 1000 == 0 ) {
                std::cout << "." ;
                std::cout.flush();
            }
            ii++;
        }
    }
    std::cout << "\nFin lecture fichier flux" << std::endl ;
}
