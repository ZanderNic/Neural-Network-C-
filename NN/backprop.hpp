#pragma once

#include "NN_new.hpp"
#include "layer.hpp"

//TODO include Fehler 
void backproperagtion(NN &network){
    std::vector<FullyConnectedLayer> layers = network.get_layers();
    std::size_t i = layers.size()-1;
    auto real = network.get_batch_classes();
    auto pred = layers[i].get_outputs();
    auto loss = network.loss_deviation_fit(real, pred);
    
    //  for(std::vector<FullyConnectedLayer> layer = layers.rbegin(); layer != layers.rend(); ++layer){
    for(; i > 0; --i){
        if (i != layers.size() - 1){
            loss = layers[i].get_loss() * layers[i + 1].get_weight();
        }
        layers[i].set_loss(loss * (network.activation_deviation(loss)));
        loss = layers[i].get_loss() * layers[i].get_input();
        network.optimizer_fit((layers[i].get_weights()), network.get_learning_rate(), loss);
    }
}

