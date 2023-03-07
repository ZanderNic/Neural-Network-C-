#pragma once 

#include "matrix.hpp"
#include "any"

namespace Optimizer{
    

    class SGD{
        public:
            SGD() = default;
            Matrix choose_points(unsigned int batch_size, Matrix &dataset);
            void fit(Matrix &weight, double lr, Matrix &loss);
            void execute(Matrix &weight, double lr, Matrix &loss);
            ~SGD() = default;
    };

    class GD{
        private:
            std::vector<Matrix> m_weight_cache;
            std::size_t m_iteration_count;
        public:
            GD() = default;
            Matrix choose_points(unsigned int batch_size, Matrix &dataset);
            void fit(Matrix &weight, double lr, Matrix &loss);
            void execute(Matrix &weight, double lr, Matrix &loss);
            ~GD() = default;
    };
}
