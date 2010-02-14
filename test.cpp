#include <iostream>
#include "matflux.h"
int verbeux = 0;
int main(int argc, char* argv[])
{
    matflux mat(4,15) ;
    mat.set_val(0,0,12) ;
    mat.set_val(0,1,14) ;
    //mat.set_val(0,3,7) ;
    mat.set_val(1,0,15) ;
    mat.set_val(1,1,17) ;
    mat.set_val(1,2,9) ;
    mat.set_val(2,1,2) ;
    mat.set_val(2,2,3) ;
    mat.set_val(2,3,1) ;
    mat.set_val(3,1,4) ;
    mat.set_val(3,3,5) ;
    //mat.set_val(9,3,12) ;
    //std::cout << mat.get_val(2,1) << "/" << mat.get_val(1,2) << "/" << mat.get_val(3,3) << std::endl ;
    mat.affiche() ;
    mat.affiche_mat() ;
    mat.merge(0,3) ;
    mat.affiche_mat() ;
    mat.merge(1,2) ;
    mat.affiche_mat() ;
    mat.merge(0,1) ;
    mat.affiche_mat() ;
    return 0;
}
