#pragma once

#include <random>

#include "matrix.hpp"
#include "vector.hpp"

class FullyConnectedLayer{
    private:
        unsigned int m_num_of_neurons;
        // all matrizes to have matrix multiplication...
        Matrix m_inputs;
        Matrix m_outputs;
        Matrix m_weights;
        Matrix m_bias;
    protected:
    public:
        FullyConnectedLayer() = delete;
        FullyConnectedLayer(unsigned int num_of_neurons) : m_num_of_neurons(num_of_neurons){
            m_bias[0] = Vector(std::vector<double>(m_num_of_neurons));
        }
        FullyConnectedLayer(unsigned int num_of_neurons, unsigned int num_of_prev_neurons);
        void init_weights(unsigned int num_of_prev_neurons);
        Matrix& get_inputs(){return m_inputs;}
        Matrix& get_outputs(){return m_outputs;}
        void set_outputs(Vector outputs){m_outputs[0] = outputs;}
        Matrix& get_weights(){return m_weights;}
        Matrix& get_biases(){return m_outputs;}
        unsigned int get_num_neurons(){return m_num_of_neurons;}
        ~FullyConnectedLayer() = default;
};

FullyConnectedLayer::FullyConnectedLayer(unsigned int num_of_neurons, unsigned int num_of_prev_neurons) : m_num_of_neurons(num_of_neurons){
    m_bias[0] = Vector(std::vector<double>(m_num_of_neurons));
    init_weights(num_of_prev_neurons);
}

void FullyConnectedLayer::init_weights(unsigned int num_of_prev_neurons){
    auto generator = std::mt19937{};
    const static double lower_bound = -1 / sqrt(num_of_prev_neurons);
    const static double upper_bound = 1 / sqrt(num_of_prev_neurons);
    auto dist = std::uniform_real_distribution<double>{lower_bound, upper_bound};

    for (std::size_t j = 0; j < m_num_of_neurons; ++j){
        // num_prev_neurons is also num_of_connection = weights_per_neuron
        auto weights_neuron = Vector(std::vector<double>(num_of_prev_neurons));
        for (std::size_t k = 0; k < num_of_prev_neurons; ++k){
            weights_neuron[k] = dist(generator);
        }

        m_weights[j] = weights_neuron;
    }

}