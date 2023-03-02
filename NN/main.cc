#include <iostream>
#include <vector>

#include "lib.h"

int main(){
    std::vector<double> p1{1.0f, 2.0f, 3.0f};
    Vector vec1(p1);
    std::cout << vec1;
}