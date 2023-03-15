#pragma once

#include <functional>
#include <string>

#include "matrix.hpp"
#include "errors.hpp"

class ActivationFunctions{
    public: 
    virtual Matrix fit(Matrix &datapoint) const = 0; //
    virtual Matrix deviation(Matrix &loss) const = 0; //
};


class Sigmoid : public ActivationFunctions{
    public:
        Sigmoid() = default;
        virtual Matrix fit(Matrix &datapoint) const override{
            Errors::only_1D_matrices(datapoint);
            auto result = Matrix(datapoint.num_rows(), 1);
            static const auto e = std::exp(1);  
            for (std::size_t i = 0; i < datapoint.num_rows(); ++i){
                auto _x = -datapoint[i][0];
                result[i][0] = (1.0 / (1.0 + std::pow(e, _x)));
            }
            return result;
        }
        

        virtual Matrix deviation(Matrix &loss) const override{
            Errors::only_1D_matrices(loss);
            auto result = (1 - loss);
            return loss * result; 
        }

        ~Sigmoid() = default;
};




class Relu : public ActivationFunctions{
        public:
            Relu() = default;
            virtual Matrix fit(Matrix &datapoint) const override{
                Errors::only_1D_matrices(datapoint);

                auto result = Matrix(datapoint.num_rows(), 1);

                for (std::size_t i = 0; i < datapoint.num_rows(); ++i){
                    if (datapoint[i][0] <= 0){
                        result[i][0] = 0;
                    }else{
                        result[i][0] = datapoint[i][0];
                    }
                }

                return result;
            }

            virtual Matrix deviation(Matrix &loss) const override{
                Errors::only_1D_matrices(loss);
                auto result = Matrix(loss.num_rows(), 1);

                for (std::size_t i = 0; i < loss.num_rows(); ++i){    
                    if (loss[i][0] <= 0){
                        result[i][0] = 0;
                    }else{
                        result[i][0] = 1;
                    }
                }   
                return result;
            }

            ~Relu() = default;
};
    
    

