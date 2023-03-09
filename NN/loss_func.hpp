#pragma once

#include "matrix.hpp"

namespace LossFunction{
    class MSE{
        MSE() = default;
        Matrix fit(Matrix &pred, Matrix &real);
        Matrix deviation(Matrix &pred, Matrix &real);
        ~MSE() = default;
    };

    using lossFunc = MSE;
    void choose_loss_func(std::string lossfunction){
        if (lossfunction == "MSE"){
            using lossFunc = MSE;
        }
    }
}