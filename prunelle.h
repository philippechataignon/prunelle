#ifndef PRUNELLE_H
#define PRUNELLE_H

void lecture_commune(std::vector<commune> & vcom , std::ifstream & com);
void lecture_flux (matflux & mflux,  std::ifstream & flu, std::vector<commune> & vcom);
#endif
