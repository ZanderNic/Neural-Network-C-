#pragma once

#include "matrix.hpp"
#include "errors.hpp"

class LossFunction
{
public:
    LossFunction() = default;
    virtual Matrix fit(Matrix &pred, Matrix &real) const = 0;
    virtual Matrix deviation(Matrix &pred, Matrix &real) const = 0;
    ~LossFunction() = default;
};




    class MSE : public LossFunction{
        public:
            MSE() = default;
            virtual Matrix fit(Matrix &pred, Matrix &real) const override{
                Errors::only_1D_matrices(pred);
                Errors::same_dimension(pred, real);
                Matrix result(pred.num_rows(), pred.num_columns());
                for (std::size_t i = 0; i < pred.num_rows(); ++i){
                    result[i][0] = (1 / 2) * std::pow((pred[i][0] - real[i][0]), 2);
                }
                return result;
            };

            virtual Matrix deviation(Matrix &pred, Matrix &real) const override{
                return pred - real;
            };
            ~MSE() = default;
        private:
        protected:
    };

   
