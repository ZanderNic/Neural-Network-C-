#pragma once

#include <functional>
#include <map>
#include <tuple>

#include "matrix.hpp"
#include "layer.hpp"
#include "activation_func.hpp"
#include "loss_func.hpp"
#include "optimizer.hpp"
#include "backprop.hpp"

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
        ActivationFunctions::actFunc get_activation_function(){return m_activation_function;}
        LossFunction::lossFunc get_loss_functions(){return m_loss_functions;}
        Optimizer::opt get_optimizier(){return m_optimizier;}
        Matrix get_input(){return m_input;}
        std::vector<FullyConnectedLayer> get_layers(){return m_layers;}
        void fit();
        ~NN() = default;
};

NN::NN(Matrix input, std::string activation_func, std::string loss_func, std::string optimizer, std::vector<FullyConnectedLayer> layers) : 
    m_activation_function(ActivationFunctions::activation_functions[activation_func]),
    m_loss_functions(LossFunction::loss_functions[loss_func]),
    m_optimizier(Optimizer::optimizer[optimizer]),
    m_layers(layers),
    m_input(input){}

// TODO: might be better to return a fitted network rather than void
void NN::fit(unsigned int epochs, unsigned int batch_size, unsigned int learning_rate){
    auto &input_layer = m_layers[0];
    m_layers.erase(m_layers.begin());
    // TODO: In question when SGD stops might be in case of convergence but not sure at all, especially
    // TODO: when convergence is reached when error changes a little?
    auto num_iterations = static_cast<int>(m_input.num_columns() / batch_size);



    for (unsigned int i = 0; i < epochs; ++i){
        while(is_converged()){

        }
        for (unsigned int i = 0; i < num_iterations; ++i)
            Matrix input = m_optimizier.choose_points(batch_size, m_input);
            for (unsigned int i = 0; i < batch_size; ++i){
                for (auto &layer : m_layers){
                    layer.set_inputs(input);
                    forward_path(layer);
                }
            }
            BackPropergation(*this);
            for (auto &layer : m_layers){
                m_optimizier.fit(layer.get_weights(), learning_rate, layer.get_loss());
            }
            input = 
    }

}

