#include "errors.hpp"

namespace Errors{
    void same_dimension(Vector &v1, Vector &v2){
        try {
            if (v1.size() != v2.size()){
                throw(DimensionError("Can't execute between different sizes."));
            }
        } catch (DimensionError e){
            std::cerr << e.what() << v1.size() << " != " << v2.size() << std::endl;
            exit(20);
        }
    }

    void same_dimension(Matrix &m1, Matrix &m2){
        try {
            if ((m1.num_columns() != m2.num_columns()) && (m1.num_rows() != m2.num_rows())){
                throw(DimensionError("Can't execute between different sizes."));
            }
        } catch (DimensionError e){
            std::cerr << e.what() << "(" << m1.num_columns() << "," << m1.num_rows() << ")" 
            << " != " << "(" << m2.num_columns() << "," << m2.num_rows() << ")" << std::endl;
            exit(20);
        }
    }

    void same_rows_to_colmns(Matrix &m1, Matrix &m2){
        try {
            if (m1.num_columns() != m2.num_rows()){
                throw(DimensionError("Can't execute between different sizes."));
            }
        } catch (DimensionError e){
            std::cerr << e.what() << " " << m1.num_columns() << " != " << m2.num_rows() << std::endl;
            exit(20);
        }
    }

    void only_1D_matrices(Matrix &m){
        try {
            if (m.num_columns() != 1){
                throw(DimensionError("Only 1D Matrices allow is"));
            }
        } catch (DimensionError e){
            std::cerr << e.what() << " " << m.num_columns() << std::endl;
            exit(20);
        }
    }
}
