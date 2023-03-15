#pragma once 

#include "matrix.hpp"

class Optimizer{
    protected:
         
    public:
        virtual std::size_t get_p_per_backprop() const = 0;
        virtual std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds);
        virtual void fit(Matrix &weight, double lr, Matrix &loss) const = 0;
};


class SGD : public Optimizer{
        private:
            std::size_t num_p_per_backprop;
        public:
            SGD() = default;
            virtual std::size_t get_p_per_backprop() const override {return num_p_per_backprop;};

            virtual std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds) override{
                num_p_per_backprop = 1;

                //TODO: Random Device Austauschen geht ned :D
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
            };

            virtual void fit(Matrix &weight, double lr, Matrix &loss) const override{
                auto result = loss * lr;
                weight -= result;
            };
            ~SGD() = default;
};



class MiniBatchGD : public Optimizer{
        private:
            std::size_t num_p_per_backprop;
            std::vector<Matrix> m_weight_cache;
            std::size_t m_iteration_count;
        public:
            MiniBatchGD() = default;
            virtual std::size_t get_p_per_backprop() const override{return num_p_per_backprop;};

            virtual std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds) override{
                num_p_per_backprop = batch_size;

                //TODO: Random Device Austauschen geht ned :D
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
            };

            virtual void fit(Matrix &weight, double lr, Matrix &loss) const override{
                auto result = loss * lr;
                weight -= result;
            };
            ~MiniBatchGD() = default;
};    

class BatchGD : public Optimizer{
        private:
            std::vector<Matrix> m_weight_cache;
            std::size_t m_iteration_count;
            std::size_t num_p_per_backprop;
        public:
            BatchGD() = default;
            virtual std::size_t get_p_per_backprop() const override{return num_p_per_backprop;};
            virtual std::tuple<Matrix, std::vector<std::size_t>> choose_points(unsigned int batch_size, Matrix ds)  override{

                //TODO:: https://stackoverflow.com/questions/34047264/assignment-of-member-in-read-only-object du kannst keine member Variable in einer const member func verändern 
                num_p_per_backprop = ds.num_rows();
                std::vector<std::size_t> indizes;
                for (std::size_t i = 0; i < num_p_per_backprop; ++i){
                    indizes.push_back(i);
                }
                return make_tuple(ds, indizes);
            };

            virtual void fit(Matrix &weight, double lr, Matrix &loss) const override{
                auto result = loss * lr;
                weight -= result;
            };
            ~BatchGD() = default;
};    



   