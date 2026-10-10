#include "CrossArray.hpp"
#include <iostream>
int main(){
    sjtu::CrossArray ca(2);
    int a[] = {1,2,3};
    ca.InsertArrays(a,3);
    const sjtu::CrossArray &c = ca;
    const int *p = c.AtArray(0);
    std::cout << p[0] << std::endl;
    return 0;
}
