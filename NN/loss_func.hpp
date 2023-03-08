#pragma once

#include "matrix.hpp"

namespace LossFunction{
    using lossFunc = std::function<double(Matrix &, Matrix &)>;

    class MSE{
        MSE() = default;
        Matrix fit(Matrix &pred, Matrix &real);
        Matrix deviation(Matrix &pred, Matrix &real);
        ~MSE() = default;
    }

}