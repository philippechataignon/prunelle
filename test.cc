#include <vector>
#include <list>

#include "matflux.h"

int main(int argc, char* argv[])
{
    matflux mat(4,10) ;
    mat.set_val(2,1,15) ;
    mat.set_val(1,2,14) ;
    mat.set_val(2,3,9) ;
    mat.set_val(1,1,12) ;
    mat.set_val(2,2,17) ;
    mat.imprime() ;
    std::cout << mat.get_val(2,1) << "/" << mat.get_val(1,2) << "/" << mat.get_val(3,3) << std::endl ;
    return 0;
}
