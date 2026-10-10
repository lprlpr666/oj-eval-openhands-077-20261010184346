#include "CrossArray.hpp"
#include <iostream>
int main(){
    sjtu::CrossArray ca(2);
    int a[] = {10,20,30};
    ca.InsertArrays(a,3);
    const sjtu::CrossArray &c = ca;
    const int *p = c.AtArray(0);
    std::cout << p[1] << std::endl;
    return 0;
}
