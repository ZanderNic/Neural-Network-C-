#include "matrix.hpp"
#include "vector.hpp"
#include "errors.hpp"

Matrix Matrix::operator+(Matrix &rhs){

    Errors::same_dimension(*this, rhs);

    auto result = Matrix();
    for(std::size_t i = 0; i < this->num_rows(); ++i){
        const auto e = this->get(i) + rhs.get(i);
        result.push_back(e);
    }

    return result;
}

Matrix Matrix::operator-(Matrix &rhs){

    Errors::same_dimension(*this, rhs);

    auto result = Matrix();

    for(std::size_t i = 0; i < this->num_rows(); ++i){
        const auto e = this->get(i) - rhs.get(i);
        result.push_back(e);
    }

    return result;
}

Matrix Matrix::operator*(Matrix &rhs){

    Errors::same_rows_to_colmns(*this, rhs);

    auto n = this->num_rows();
    auto m = rhs.num_columns();
    auto result = Matrix(n, m);
 
    for (std::size_t i = 0; i < this->num_rows(); ++i){
        for (std::size_t j = 0; j < rhs.num_columns(); ++j){
            for (std::size_t k = 0; k < this->num_columns(); ++k){
                result[i][j] += this->get(i)[k] * rhs[k][j];
            }
        }
    }

    return result;
};

void Matrix::operator+=(Matrix &rhs){

    Errors::same_dimension(*this, rhs);

    for(std::size_t i = 0; i < this->num_rows(); ++i){
        this->set(i, this->get(i) + rhs[i]);
    }
}

void Matrix::operator-=(Matrix &rhs){
   
    Errors::same_dimension(*this, rhs);

    for(std::size_t i = 0; i < this->num_rows(); ++i){
        this->set(i, this->get(i) - rhs[i]);
    }
}

void Matrix::operator*=(Matrix &rhs){

    Errors::same_rows_to_colmns(*this, rhs);

    for(std::size_t i = 0; i < this->num_rows(); ++i){
        for (std::size_t k = 0; k < rhs.num_columns(); ++k){
            for(std::size_t j = 0; j < rhs.num_rows(); ++j){
                this->get(i).set(j, this->get(i).get(j) * rhs[k][j]);
            }
        }
    }
}