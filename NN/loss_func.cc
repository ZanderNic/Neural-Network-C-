#include "loss_func.hpp"
#include "matrix.hpp"
#include "utils.hpp"

namespace LossFunction{
    std::map<std::string, lossFunc>loss_functions = {
        {"MSE", MSE},
    };

    double MSE(Matrix &pred, Matrix &real){
        Errors::same_dimension(pred, real);

        double sum = 0.0;

        for (std::size_t i = 0; i < pred.num_rows(); ++i){
            sum += std::pow((pred[i][0] - real[i][0]), 2);
        }

        return sum / pred.num_rows();
    }
}