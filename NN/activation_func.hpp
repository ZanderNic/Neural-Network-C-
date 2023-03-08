#pragma once

#include <functional>
#include <map>

#include "matrix.hpp"

namespace ActivationFunctions{
    using actFunc = std::function<Matrix(Matrix &)>;

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

    extern std::map<std::string, ActivationFunctions::actFunc>activation_functions;
}