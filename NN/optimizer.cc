#include <vector>
#include <random>
#include <tuple>

#include "optimizer.hpp"
namespace Optimizer{
    std::map<std::string, opt>optimizer = {
        {"SGD", SGD()},
        {"MiniBatchGD", MiniBatchGD()},
        {"BatchGD", BatchGD()},
    };

    class SGD{
        private:
            std::size_t num_p_per_backprop;
        public:
            SGD() = default;
            std::size_t get_p_per_backprop(){return num_p_per_backprop;}
            std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds){
                num_p_per_backprop = 1;
                static std::random_device seed;
                static auto generator = std::mt19937{seed};
                static auto dist = std::uniform_real_distribution<std::size_t>{0, ds.num_rows() - 1};
                
                // batch of SGD consists just of a single datapoint
                Matrix batch(num_p_per_backprop, ds.num_columns()); 
                std::vector<std::size_t> indizes;

                auto index = dist(generator);
                indizes.push_back(index);
                batch[0] = ds[index];

                return make_tuple(batch, indizes);
            }

            void fit(Matrix &weight, double lr, Matrix &loss){
                auto result = loss * lr;
                weight -= result;
            }
            ~SGD() = default;
    };

    class MiniBatchGD{
        private:
            std::size_t num_p_per_backprop;
        public:
            MiniBatchGD() = default;
            std::size_t get_p_per_backprop(){return num_p_per_backprop;}
            std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds){
                num_p_per_backprop = batch_size;
                static std::random_device seed;
                static auto generator = std::mt19937{seed};
                static auto dist = std::uniform_real_distribution<std::size_t>{0, ds.num_rows() - 1};
                
                Matrix batch(batch_size, ds.num_columns());
                std::vector<std::size_t> indizes;

                for (std::size_t c = 0; c < batch_size; ++c){
                    auto index = dist(generator);
                    indizes.push_back(index);
                    batch[c] = ds[index];
                }

                return make_tuple(batch, indizes);
            }
    
            void fit(Matrix &weight, double lr, Matrix &loss){
                auto result = loss * lr;
                weight -= result;
            }
            ~MiniBatchGD() = default;
    };

    class BatchGD{
        private:
            std::size_t num_p_per_backprop;
        public:
            BatchGD() = default;
            std::size_t get_p_per_backprop(){return num_p_per_backprop;}
            std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds){
                num_p_per_backprop = ds.num_rows();
                std::vector<std::size_t> indizes;
                for (std::size_t i = 0; i < num_p_per_backprop; ++i){
                    indizes.push_back(i);
                }

                return make_tuple(ds, indizes);
            }
    
            void fit(Matrix &weight, double lr, Matrix &loss){
                auto result = loss * lr;
                weight -= result;
            }

            ~BatchGD() = default;
    };
}