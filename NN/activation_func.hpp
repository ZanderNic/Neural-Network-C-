#pragma once

#include <functional>
#include <map>

#include "matrix.hpp"

namespace ActivationFunctions{
    using actFunc = std::function<Matrix(Matrix &)>;

    Matrix sigmoid(Matrix &m);
    Matrix relu(Matrix &m);

    extern std::map<std::string, ActivationFunctions::actFunc>activation_functions;
}