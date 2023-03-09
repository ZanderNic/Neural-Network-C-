#pragma once 

#include "matrix.hpp"

namespace Optimizer{
    class SGD{
        public:
            SGD() = default;
            std::size_t get_p_per_backprop();
            std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds);
            void fit(Matrix &weight, double lr, Matrix &loss);
            ~SGD() = default;
    };

    class MiniBatchGD{
        private:
            std::vector<Matrix> m_weight_cache;
            std::size_t m_iteration_count;
        public:
            MiniBatchGD() = default;
            std::size_t get_p_per_backprop();
            std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds);
            void fit(Matrix &weight, double lr, Matrix &loss);
            ~MiniBatchGD() = default;
    };

    class BatchGD{
        private:
            std::vector<Matrix> m_weight_cache;
            std::size_t m_iteration_count;
        public:
            BatchGD() = default;
            std::size_t get_p_per_backprop();
            std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds);
            void fit(Matrix &weight, double lr, Matrix &loss);
            ~BatchGD() = default;
    };

    using opt = SGD;
    void choose_optimizer(std::string optimizer){
        if (optimizer == "SGD"){
            using opt = SGD;
        } else if (optimizer == "MiniBatchGD"){
            using opt = MiniBatchGD;
        } else if (optimizer == "BatchGD"){
            using opt = BatchGD;
        }
    }
}
