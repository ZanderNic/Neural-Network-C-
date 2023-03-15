#include <iostream>
#include <vector>

#include "NN_new.hpp"
#include "matrix.hpp"



int main(){
    auto a = Matrix(5, 10);
    std::cout << a[0];


    Matrix Input = {10,10};
    for(size_t i = 0; i < 10; i++){
        for(size_t u = 0; u < 10; ++u){
            Input[i][u] = i * u;
        }
    }

    std::vector<int> classes;
    for(int i = 0; i < 10; ++i){
        classes.push_back(i);
    }

    std::string activation_function;
    activation_function = "Sigmoid";

    std::string loss_function;
    loss_function = "MSE";

    std::string optimizer;
    optimizer = "SGD";


    std::vector<FullyConnectedLayer> Layers;
    Layers.push_back({50, 10});
    Layers.push_back({30,50});
    Layers.push_back({10,30});

    //TODO: Includes fixen 
    NN neuralNetwork(Input, classes, activation_function, loss_function, optimizer, Layers);
   
    //TODO: Es Hier wird die Learnig rate festgelgt die wird gebraucht beim Optimizer ist aber nicht im NN selbst gespeichert, ist schon gelöst aber ned schön  
    neuralNetwork.fit(20,1,0.5);



}