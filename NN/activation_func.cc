#include "activation_func.hpp"
#include "errors.hpp"

namespace ActivationFunctions{
    std::map<std::string, ActivationFunctions::actFunc>activation_functions = {
        {"sigmoid", sigmoid()},
        {"relu", relu()},
    };

    Matrix Sigmoid::fit(Matrix &datapoint){
        Errors::only_1D_matrices(datapoint);

        auto result = Matrix(datapoint.num_rows(), 1);

        static const auto e = std::exp(1);
        
        for (std::size_t i = 0; i < datapoint.num_rows(); ++i){
            auto _x = -datapoint[i][0];
            result[i][0] = (1.0 / (1.0 + std::pow(e, _x)));
        }

        return result;
    }

    Matrix Sigmoid::deviation(Matrix &loss){
        Errors::only_1D_matrices(loss);
        auto result = (1 - loss);
        return loss * result;
    }

    Matrix Relu::fit(Matrix &datapoint){
        Errors::only_1D_matrices(datapoint);

        auto result = Matrix(datapoint.num_rows(), 1);

        for (std::size_t i = 0; i < datapoint.num_rows(); ++i){
            if (datapoint[i][0] <= 0){
                result[i][0] = 0;
            } else{
                result[i][0] = datapoint[i][0];
            }
        }

        return result;
    }

    Matrix Relu::deviation(Matrix &loss){
        Errors::only_1D_matrices(loss);

        for (std::size_t i = 0; i < loss.num_rows(); ++i){
            if (loss[i][0] <= 0){
                result[i][0] = 0;
            } else{
                result[i][0] = 1;
            }
        }
        return result;
    }

}

