#pragma once 

#include "matrix.hpp"

namespace Optimizer{
    using opt = std::function<void(Matrix &, double, Matrix &)>;
    void SGD(Matrix &weight, double lr, Matrix &loss);

    extern std::map<std::string, opt>optimizer;
};

