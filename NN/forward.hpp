#pragma once

#include "layer.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "utils.hpp"

void forward_path(FullyConnectedLayer layer){
    // weights @ inputs + bias = Ouputs
    std::cout << "Inputs: \n";
    std::cout << layer.get_inputs();
    std::cout << "Weights: \n";
    std::cout<< layer.get_weights() ;
    
    
    Matrix output_((layer.get_inputs() * layer.get_weights()));
    std::cout << output_ ;
}