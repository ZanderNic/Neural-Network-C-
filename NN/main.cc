#include <iostream>
#include <vector>

#include "layer.hpp"
#include "forward.hpp"
#include "matrix.hpp"
#include "NN.hpp"

int main(){
    FullyConnectedLayer l(5, 10);
    forward_path(l);
}