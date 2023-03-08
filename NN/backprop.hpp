#pragma once

#include "NN.hpp"

void backproperagtion(NN &network){
    auto layers = network.get_layers();
    auto real = network.get_batch_classes();
    auto pred = layers.back().get_outputs();
    auto loss = network.get_loss_functions().fit(real, pred);

    for (auto layer = layers.rbegin(), std::size_t i = layers.size() - 1; layer != layers.rend(); ++layer, --i){
        if (i != layers.size() - 1){
            loss = *layer.get_loss() * layer[i + 1].get_weight();
        }
        *layer.set_loss(loss * network.get_activation_function().deviation(loss));
        loss = *layer.get_loss() * *layer.get_input();
        m_optimizier(*layer.get_weights(), network.get_learning_rate(), loss);
    }
}
