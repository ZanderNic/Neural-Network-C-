#pragma once

#include <functional>
#include <map>

#include "matrix.hpp"
#include "layer.hpp"
#include "activation_func.hpp"
#include "loss_func.hpp"
#include "optimizer.hpp"

class NN{
    private:
        ActivationFunctions::actFunc m_activation_function;
        LossFunction::lossFunc m_loss_functions;
        Optimizer::opt m_optimizier;
        Matrix m_input;
        std::vector<FullyConnectedLayer> m_layers;
    protected:
    public:
        NN() = delete;
        NN(Matrix input, std::string activation_func, std::string loss_func, std::string optimizer, std::vector<FullyConnectedLayer> layers);

        ~NN() = default;
};

NN::NN(Matrix input, std::string activation_func, std::string loss_func, std::string optimizer, std::vector<FullyConnectedLayer> layers) : 
    m_activation_function(ActivationFunctions::activation_functions[activation_func]),
    m_loss_functions(LossFunction::loss_functions[loss_func]),
    m_optimizier(Optimizer::optimizer[optimizer]),
    m_layers(layers),
    m_input(input){
    //TODO: Build the network from Inputs
}