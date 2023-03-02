#pragma once

namespace Errors{
    class DimensionError : public std::exception {
        public:
            DimensionError(std::string_view _message) : message(_message){};

            std::string message;

            [[nodiscard("Error Message")]] const char *what() const noexcept override{
                return message.c_str();
            }
    };

    void same_dimension(Vector &v1, Vector &v2){
        try {
            if (v1.size() != v2.size()){
                throw(DimensionError("Can't execute between different sizes."));
            }
        } catch (DimensionError e){
            std::cerr << e.what() << v1.size() << " != " << v2.size() << std::endl;
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
        }
    }

    void same_rows_to_colmns(Matrix &m1, Matrix &m2){
        try {
            if (m1.num_rows() != m2.num_columns()){
                throw(DimensionError("Can't execute between different sizes."));
            }
        } catch (DimensionError e){
            std::cerr << e.what() << m1.num_columns() << " != " << m2.num_rows() << std::endl;
        }
    }
}