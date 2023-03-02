#pragma once

#include "vector.hpp"
#include "matrix.hpp"

namespace Utils{
    Vector matrix_to_vector(Matrix m){
        return m[0];
    }
}