#pragma once 

#include "matrix.hpp"
#include "any"

class Optimizer{
    Optimizer() = default;
    ~Optimizer() = default;
    Optimizer(std::string act);

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
};
