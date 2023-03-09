#pragma once

#include <functional>
#include <map>

#include "matrix.hpp"

namespace ActivationFunctions{
    class Sigmoid{
        public:
            Sigmoid() = default;
            Matrix fit(Matrix &datapoint);
            Matrix deviation(Matrix &loss);
    };

    class Relu{
        public:
            Relu() = default;
            Matrix fit(Matrix &datapoint);
            Matrix deviation(Matrix &loss);
    };

    using actFunc = Sigmoid;
    void choose_activation_func(std::string activationfunc){
        if (activationfunc == "sigmoid"){
            using actFunc = Sigmoid;
        } else if (activationfunc == "relu"){
            using actFunc = Relu;
        }
    }
}