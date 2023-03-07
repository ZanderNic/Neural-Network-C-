#pragma once

#include "layer.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "activation_func.hpp"

void forward_path(FullyConnectedLayer &layer){
    // weights @ inputs + bias = Ouputs

    auto output_ = (layer.get_weights() * layer.get_inputs()) + layer.get_biases();

    layer.set_outputs(ActivationFunctions::sigmoid(output_)); 
}