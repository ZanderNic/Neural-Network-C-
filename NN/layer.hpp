#pragma once

#include <random>

#include "matrix.hpp"
#include "vector.hpp"
#include "forward.hpp"

class FullyConnectedLayer{
    private:
    protected:
        unsigned int m_num_of_neurons;
        unsigned int m_num_of_prev_neurons;
        // all matrizes to have matrix multiplication...
        Matrix m_inputs;
        Matrix m_outputs;
        Matrix m_weights;
        Matrix m_loss;
        Matrix m_bias;
    public:
        FullyConnectedLayer() = delete;
        FullyConnectedLayer(unsigned int num_of_neurons);
        FullyConnectedLayer(unsigned int num_of_neurons, unsigned int num_of_prev_neurons);
        void init_weights(unsigned int num_of_prev_neurons, unsigned int num_of_neurons);
        void init_bias(unsigned int num_of_neurons);
        Matrix& get_inputs(){return m_inputs;}
        Matrix& get_outputs(){return m_outputs;}
        void set_outputs(Matrix const &outputs){m_outputs = outputs;}
        void set_inputs(Matrix const &inputs){m_inputs = inputs;}
        void set_weights(Matrix const &weights){m_weights = weights;}
        void set_loss(Matrix const &loss){m_loss = loss;}
        Matrix& get_weights(){return m_weights;}
        Matrix& get_biases(){return m_bias;}
        Matrix& get_loss(){return m_loss;}
        unsigned int get_num_neurons(){return m_num_of_neurons;}
        unsigned int get_num_of_prev_neurons(){return m_num_of_prev_neurons;}
        ~FullyConnectedLayer() = default;
};

// This constructor is for all the other Layers
FullyConnectedLayer::FullyConnectedLayer(unsigned int num_of_neurons, unsigned int num_of_prev_neurons) : 
        m_num_of_neurons(num_of_neurons), 
        m_num_of_prev_neurons(num_of_prev_neurons),
        m_inputs(Matrix(m_num_of_prev_neurons, 1)),
        m_outputs(Matrix(m_num_of_neurons, 1)),
        m_weights(Matrix(m_num_of_neurons, m_num_of_prev_neurons)),
        m_bias(Matrix(m_num_of_neurons, 1)),
        m_loss(Matrix(m_num_of_neurons, m_num_of_prev_neurons)) {
    
    init_bias(num_of_neurons);
    init_weights(num_of_neurons, num_of_prev_neurons);
}

void FullyConnectedLayer::init_weights(unsigned int num_of_neurons, unsigned int num_of_prev_neurons){
    std::random_device seed;
    auto generator = std::mt19937{seed};
    const static double lower_bound = -1 / sqrt(num_of_prev_neurons);
    const static double upper_bound = 1 / sqrt(num_of_prev_neurons);
    auto dist = std::uniform_real_distribution<double>{lower_bound, upper_bound};

    for (std::size_t j = 0; j < num_of_neurons; ++j){
        // num_prev_neurons is also num_of_connection = weights_per_neuron
        for (std::size_t k = 0; k < m_num_of_prev_neurons; ++k){
            m_weights.get(j)[k] = dist(generator);
        }
    }
}

void FullyConnectedLayer::init_bias(unsigned int num_of_neurons){
    for(std::size_t i = 0; i < num_of_neurons; i++){
        m_bias[i][0] = 1;
    }
}

class InputLayer : public FullyConnectedLayer{
    private:
        Matrix m_dataset;
    protected:
    public:
        InputLayer() = delete;
        InputLayer(Matrix dataset);
        std::size_t num_datapoints(){return m_dataset.num_rows();}
        std::size_t num_dimensions(){return m_dataset.num_columns();}
        Matrix& get_dataset(){return m_dataset;}
        ~InputLayer() = default;
};

// This constructor is for the Input Layer(first layer)
InputLayer::InputLayer(Matrix dataset) :
        FullyConnectedLayer(dataset.num_rows(), dataset.num_columns()),
        m_dataset(dataset){
    init_bias(dataset.num_rows());
}