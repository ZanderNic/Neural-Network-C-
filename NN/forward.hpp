#pragma once

#include "layer.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "activation_func.hpp"

void forward_path(FullyConnectedLayer layer){
    // weights @ inputs + bias = Ouputs
    // layer.set_inputs();
    std::cout << "Weights: \n";
    std::cout<< layer.get_weights() ;
    std::cout << "Inputs: \n";
    std::cout << layer.get_inputs();
    
    auto output_ = (layer.get_weights() * layer.get_inputs()) + layer.get_biases();

    layer.set_outputs(ActivationFunctions::sigmoid(output_)); 

    std::cout << "Output: \n";
    std::cout << layer.get_outputs();
}