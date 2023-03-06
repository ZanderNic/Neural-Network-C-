#include "optimizer.hpp"

namespace Optimizer{
    std::map<std::string, opt>optimizer = {
        {"SGD", SGD},
    };

    void SGD(Matrix &weight, double lr, Matrix &loss){
        auto result = loss * lr;
        weight -= result;
    }
}
