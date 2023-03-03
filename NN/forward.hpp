#pragma once

#include "layer.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "utils.hpp"

void forward_path(FullyConnectedLayer layer){
    // weights @ inputs + bias = Ouputs
    Matrix output_ = (layer.get_weights() * layer.get_inputs());// + layer.get_biases();

    //Vector output = Utils::matrix_to_vector(output_);
    //layer.set_outputs(output);
    //std::cout << layer.get_outputs();
}