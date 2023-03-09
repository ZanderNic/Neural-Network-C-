#pragma once

#include <functional>
#include <map>
#include <tuple>
#include <vector>

#include "matrix.hpp"
#include "layer.hpp"
#include "activation_func.hpp"
#include "loss_func.hpp"
#include "optimizer.hpp"
#include "backprop.hpp"
#include "errors.hpp"
#include "forward.hpp"

class NN{
    private:
        ActivationFunctions::actFunc m_activation_function;
        LossFunction::lossFunc m_loss_functions;
        Optimizer::opt m_optimizier;
        Matrix m_input;
        std::vector<int> m_classes;
        Matrix m_batch_classes;
        InputLayer m_input_layer;
        std::vector<FullyConnectedLayer> m_layers;
    protected:
    public:
        NN() = delete;
        NN(Matrix input, std::vector<int> classes, std::string activation_func, std::string loss_func, std::string optimizer, std::vector<FullyConnectedLayer> layers);
        ActivationFunctions::actFunc get_activation_function(){return m_activation_function;}
        LossFunction::lossFunc get_loss_functions(){return m_loss_functions;}
        Optimizer::opt get_optimizier(){return m_optimizier;}
        Matrix& get_input(){return m_input;}
        InputLayer& get_input_layer(){return m_input_layer;}
        Matrix get_batch_classes(){return m_batch_classes;}
        bool is_converged(Matrix &current_loss, Matrix &prev_loss);
        std::vector<FullyConnectedLayer>& get_layers(){return m_layers;}
        void fit(unsigned int epochs, unsigned int batch_size, unsigned int learning_rate);
        ~NN() = default;
};

NN::NN(Matrix input, std::vector<int> classes, std::string activation_func, std::string loss_func, std::string optimizer, std::vector<FullyConnectedLayer> layers) : 
    m_activation_function(ActivationFunctions::choose_activation_func(activation_func)),
    m_loss_functions(LossFunction::choose_loss_func(loss_func)),
    m_optimizier(Optimizer::choose_optimizer(optimizer)),
    m_layers(layers),
    m_input(input),
    m_classes(classes){}

// TODO: might be better to return a fitted network rather than void
void NN::fit(unsigned int epochs, unsigned int batch_size, unsigned int learning_rate){

    auto num_iterations = static_cast<int>(m_input.num_rows() / m_optimizier.get_p_per_backprop());

    for (unsigned int i = 0; i < epochs; ++i){
        for (unsigned int j = 0; j < num_iterations; ++j){
            auto [batch, class_indizes] = m_optimizier.choose_points(batch_size, m_input);
            m_batch_classes = {};
            for (auto &c : class_indizes){
                Vector v(1, static_cast<double>(m_classes[c]));
                m_batch_classes.push_back(v);
            }
            m_input_layer.set_input(batch);
            forward_path(*this);
            backproperagtion(*this); 
        }
    }
}

