#pragma once

#include "matrix.hpp"

namespace LossFunction{
    using lossFunc = std::function<double(Matrix &, Matrix &)>;
    double MSE(Matrix &pred, Matrix &real);

    extern std::map<std::string, lossFunc>loss_functions;
}