#include "activation_func.hpp"
#include "errors.hpp"

namespace ActivationFunctions{
    std::map<std::string, ActivationFunctions::actFunc>activation_functions = {
        {"sigmoid", sigmoid},
        {"relu", relu},
    };

    Matrix sigmoid(Matrix &m){

        Errors::only_1D_matrices(m);

        auto result = Matrix(m.num_rows(), 1);

        static const auto e = std::exp(1);
        
        for (std::size_t i = 0; i < m.num_rows(); ++i){
            auto _x = -m[i][0];
            result[i][0] = (1.0 / (1.0 + std::pow(e, _x)));
        }

        return result;
    }

    Matrix relu(Matrix &m){

        Errors::only_1D_matrices(m);

        auto result = Matrix(m.num_rows(), 1);

        for (std::size_t i = 0; i < m.num_rows(); ++i){
            if (m[i][0] <= 0){
                result[i][0] = 0;
            } else{
                result[i][0] = m[i][0];
            }
        }

        return result;
    }
}