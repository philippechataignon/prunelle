#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <algorithm>

#include "element.h"

int main(int argc, char* argv[])
{
    element z(3,4) ;
    element w;
    w = z;
    element x(2,1) ;

    typedef std::set<element> ligcol ;

    ligcol l;

    l.insert(z) ;
    l.insert(element(4,9)) ;
    l.insert(x) ;
    
    ligcol m ;
    m.insert(element(2,6)) ;
    m.insert(element(3,5)) ;

    std::multiset<element> n ;
    
    copy(l.begin(), l.end(), std::ostream_iterator<element>(std::cout," "));
    std::cout << std::endl ;
    copy(m.begin(), m.end(), std::ostream_iterator<element>(std::cout," "));
    std::cout << std::endl ;

       merge (l.begin(), l.end(),
              m.begin(), m.end(),
              std::inserter(n,n.end()));
    

    std::multiset<element>::iterator i,j ;

    for (i=n.begin() ; i != n.end() ; i++) {
        j = i ;
        j++ ;
        if (j != n.end() ) {
            if (i->numlc == j->numlc) {
                int tmp_val = i->numval + j->numval ;
                std::cout << tmp_val << std::endl ;
                n.erase(*i) ;
                n.insert(element(i->numlc,tmp_val)) ;
            }
        }
    }
    
    copy(n.begin(), n.end(), std::ostream_iterator<element>(std::cout," "));
    std::cout << std::endl ;
    return 0;
}
