#pragma once

#include "matrix.hpp"
#include "vector.hpp"


namespace Errors{
    class DimensionError : public std::exception {
        public:
            DimensionError(std::string_view _message) : message(_message){};

            std::string message;

            [[nodiscard("Error Message")]] const char *what() const noexcept override{
                return message.c_str();
            }
    };

    void same_dimension(Vector &v1, Vector &v2);
    void same_dimension(Matrix &m1, Matrix &m2);
    void same_rows_to_colmns(Matrix &m1, Matrix &m2);

};
