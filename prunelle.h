#ifndef PRUNELLE_H
#define PRUNELLE_H

void affiche(std::vector<commune> & vcom , listeflux & lflux , listeent & lent);
void affiche(std::vector<commune> & vcom ,listeflux & lflux , listeent & lent , int numdc) ;
void lecture_commune(std::vector<commune> & vcom , std::ifstream & com);
void lecture_flux (std::vector<commune> & vcom , listeflux & lflux , listeent & lent , std::ifstream & flu);
#endif
