#include <vector>

#include "optimizer.hpp"
namespace Optimizer{
    std::map<std::string, opt>optimizer = {
        {"SGD", SGD()},
        {"GD", BatchGD()},
    };

    class SGD{
        public:
            SGD() = default;
            Matrix choose_points(){

            }
            void fit(Matrix &weight, double lr, Matrix &loss){
                auto result = loss * lr;
                weight -= result;
            }
            ~SGD() = default;
    };

    class BatchGD{
        public:
            BatchGD() = default;
            Matrix choose_points(){

            }
            void fit(Matrix &weight, double lr, Matrix &loss){
                auto result = loss * lr;
                weight -= result;
            }

            ~BatchGD() = default;
    };
}
