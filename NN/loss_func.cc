#include "loss_func.hpp"
#include "matrix.hpp"
#include "utils.hpp"

namespace LossFunction{
    Matrix MSE::fit(Matrix &pred, Matrix &real){
        Errors::only_1D_matrices(pred);
        Errors::same_dimension(pred, real);
        

        Matrix result(pred.num_rows(), pred.num_columns());

        for (std::size_t i = 0; i < pred.num_rows(); ++i){
            result[i][0] = (1 / 2) * std::pow((pred[i][0] - real[i][0]), 2);
        }

        return result;
    }
    Matrix MSE::deviation(Matrix &pred, Matrix &real){
        return pred - real;
    }
}