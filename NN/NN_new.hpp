#pragma once

#include <functional>
#include <vector>

#include "matrix.hpp"
#include "layer.hpp"
#include "activation_func_new.hpp"
#include "loss_func_new.hpp"
#include "optimizer_new.hpp"
#include "backprop.hpp"
#include "errors.hpp"
#include "forward.hpp"

class NN{
    private:
        ActivationFunctions* m_activation_function; //Pointer to Relu or Sigmoid  
        Relu m_relu;
        Sigmoid m_sigmoid;

        LossFunction* m_loss_functions; //Pointer to the selected Loss Funk
        MSE m_mse;


        Optimizer* m_optimizier; // Pointer to the selected Optimizer
        SGD m_sgd;
        MiniBatchGD m_mini_batch_gd;    
        BatchGD m_batch_gd;


        Matrix m_input;
        std::vector<int> m_classes;
        Matrix m_batch_classes;
        InputLayer m_input_layer;
        std::vector<FullyConnectedLayer> m_layers;
        unsigned int m_learning_rate;
        
        void choose_act_func(std::string &activation_func){
            if(activation_func == "sigmoid"){
                m_activation_function = &m_sigmoid;
            }else if(activation_func == "relu"){
                m_activation_function = &m_relu;
            }else{
                std::cout << "No valid Argument for activation_func" << std::endl;
            }
        }

        void choose_loss_func(std::string &loss_func){
            if(loss_func == "sigmoid"){
                m_loss_functions = &m_mse;
            }else{
                std::cout << "No valid Argument for loss_func" << std::endl;
            }
        }

        void choose_optimizer(std::string &optimizer){
            if(optimizer == "SGD"){
               m_optimizier = &m_sgd; 
            }else if (optimizer == "MiniBatchGD"){
                m_optimizier = &m_mini_batch_gd;
            }else if (optimizer == "BatchGD"){
                m_optimizier = &m_batch_gd;
            }else{
                std::cout << "No valid Argument for Optimizer" << std::endl;
            }
        }

        void set_learning_rate(unsigned int learnig_rate){m_learning_rate = learnig_rate;}

    protected:
    public:
        NN() = delete;
        NN(Matrix input, std::vector<int> classes, std::string activation_func, std::string loss_func, std::string optimizer, std::vector<FullyConnectedLayer> layers) :   
            m_layers(layers),
            m_input(input),
            m_classes(classes),
            m_input_layer(input){
                choose_act_func(activation_func);            
                choose_loss_func(loss_func);
                choose_optimizer(optimizer);
        }
        
        Matrix activation_fit(Matrix &datapoint) const{
            return m_activation_function->fit(datapoint);
        }
        Matrix activation_deviation(Matrix &loss) const{
            return m_activation_function->deviation(loss);
        }

        Matrix loss_fit(Matrix &pred, Matrix &real){
            return m_loss_functions->fit(pred, real);
        }
        Matrix loss_deviation_fit(Matrix &pred, Matrix &real){
            return m_loss_functions->deviation(pred, real);
        }

        std::size_t optimizer_get_p_per_backprop(){
            return m_optimizier->get_p_per_backprop();
        }   
        std::tuple<Matrix, std::vector<std::size_t>> optimizer_choose_points(unsigned int batch_size, Matrix ds){
            return m_optimizier->choose_points(batch_size, ds);
        }
        void optimizer_fit(Matrix &weight, double lr, Matrix &loss){
            return m_optimizier->fit(weight, lr, loss);
        }

        Matrix& get_input(){return m_input;}
        InputLayer& get_input_layer(){return m_input_layer;}
        Matrix get_batch_classes(){return m_batch_classes;}
        bool is_converged(Matrix &current_loss, Matrix &prev_loss);
        std::vector<FullyConnectedLayer>& get_layers(){return m_layers;}
        void fit(unsigned int epochs, unsigned int batch_size, unsigned int learning_rate);
        unsigned int get_learning_rate(){return m_learning_rate;}
        ~NN() = default;
};




// TODO: might be better to return a fitted network rather than void

void NN::fit(unsigned int epochs, unsigned int batch_size, unsigned int learning_rate){
    //Mega scheiße gemacht :D aber ist kein Fehler liegt auch an dem Oben :D
    int learnig_rate;
    set_learning_rate(learning_rate);
    auto num_iterations = static_cast<int>(m_input.num_rows() / optimizer_get_p_per_backprop());

    for(unsigned int i = 0; i < epochs; ++i){
        for(unsigned int j = 0; j < num_iterations; ++j){
            auto [batch, class_indizes] = optimizer_choose_points(batch_size, m_input);
            m_batch_classes = {};
            for (auto &c : class_indizes){
                Vector v(1, static_cast<double>(m_classes[c]));
                m_batch_classes.push_back(v);
            }
            this->m_input_layer.set_inputs(batch);

            //TODO: includes fixen da es bei forward unf backprop ned mit include klappt sind das keine Funktionen die Aufgerufen werden können 
            forward_path(*this);
            backproperagtion(*this); 
        }
    }
}
