#pragma once

#include "layer.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "NN_new.hpp"


//TODO: Das problem liegt an include es wird NN nicht erkannt 
void forward_path(NN &network){
    auto input_layer = network.get_input_layer();
    for (std::size_t i = 0; i < input_layer.num_datapoints(); ++i){
        auto output = input_layer.get_dataset()[i];
        for (auto &layer : (network.get_layers())){
            layer.set_input(output);
            // weights @ inputs + bias = Ouputs
            auto output_ = (layer.get_weights() * layer.get_inputs()) + layer.get_biases();

            layer.set_outputs(network.activation_fit(output_)); 
        }
    }
}