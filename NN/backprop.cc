#include "optimizer.hpp"
#include "matrix.hpp"
#include "NN.hpp"

class BackPropergation{
    private:
    protected:
    public:
        BackPropergation(NN &network){
            for (auto &layer : network.get_layers()){
                
            }
        };

        Matrix MSE_dev(Matrix &real, Matrix &pred){
            return (real - pred);
        };

        Matrix sigmoid_dev(Matrix &output){
            auto result = (1 - output);
            return output * result;
        }
};
