#include "optimizer.hpp"
#include "matrix.hpp"
#include "createNN.hpp"

class BackPropergation{
    private:
    protected:
    public:
        BackPropergation(NN network){
            while(m.get_errors()){

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
