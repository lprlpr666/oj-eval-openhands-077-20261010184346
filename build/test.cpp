#include "CrossArray.hpp"
#include <iostream>
int main(){
    sjtu::CrossArray ca(2);
    int a[] = {1,2,3};
    ca.InsertArrays(a,3);
    const int *p = ca.AtArray(0);
    std::cout << p[0] << " " << p[2] << std::endl;
    int b[] = {4,5};
    ca.AppendArrays(b,0,2);
    const int *p2 = ca.AtArray(0);
    std::cout << p2[3] << std::endl;
    sjtu::CrossArray ca2(2);
    int c[] = {1};
    ca2.InsertArrays(c,1);
    sjtu::CrossArray &greater = ca.WhichGreater(ca2);
    std::cout << ( &greater == &ca ? "ca" : "ca2" ) << std::endl;
    std::cout << ca.IsSame(ca) << " " << ca.IsSame(ca2) << std::endl;
    ca.DoubleCrossLength();
    std::cout << "done" << std::endl;
    return 0;
}
