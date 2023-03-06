#pragma once

#include "vector.hpp"
#include "matrix.hpp"
#include "errors.hpp"

namespace Utils{
    Vector matrix_to_vector(Matrix m){

        Errors::only_1D_matrices(m);

        auto result = Vector();
        
        for (std::size_t i = 0; i < m.num_rows(); ++i){
            result[i] = m[i][0];
        }

        return result;
    }
}