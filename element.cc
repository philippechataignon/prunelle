#include <iostream>
#include "element.h"

std::ostream & operator << (std::ostream & os, const element & element)
{
        std::cout << "{" << element.numlc << "," << element.numval << "} " ;
        return os;
}
