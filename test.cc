#include "matflux.h"

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
    mat.set_val(3,3,6) ;
    mat.imprime() ;
    std::cout << mat.get_val(2,1) << "/" << mat.get_val(1,2) << "/" << mat.get_val(3,3) << std::endl ;
    mat.merge(0,3) ;
    mat.imprime() ;
    return 0;
}
