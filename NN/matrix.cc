#include "matrix.hpp"
#include "vector.hpp"
#include "errors.hpp"

Matrix Matrix::operator+(Matrix &rhs){

    Errors::same_dimension(*this, rhs);

    auto result = Matrix();
    for(std::size_t i = 0; i < this->num_columns(); ++i){
        const auto e = this->get(i) + rhs.get(i);
        result.push_back(e);
    }

    return result;
}

Matrix Matrix::operator-(Matrix &rhs){

    Errors::same_dimension(*this, rhs);

    auto result = Matrix();

    for(std::size_t i = 0; i < this->num_columns(); ++i){
        const auto e = this->get(i) - rhs.get(i);
        result.push_back(e);
    }

    return result;
}

Matrix Matrix::operator*(Matrix &rhs){

    Errors::same_dimension(*this, rhs);

    auto result = Matrix();

    if(this->num_columns() != rhs.num_rows()){
        throw std::invalid_argument ("Matrixen sind ned für Multiplickation geigenet");
    }

    for(std::size_t i = 0; i < this->num_rows(); ++i){
        for (std::size_t k = 0; k < rhs.num_columns(); ++k){
            for(std::size_t j = 0; j < rhs.num_rows(); ++j){
                result[i].set(j, result[i][j] * rhs[i][j]);
            }
        }
    }

    return result;
};

void Matrix::operator+=(Matrix &rhs){

    Errors::same_dimension(*this, rhs);

    for(std::size_t i = 0; i < this->num_columns(); ++i){
        this->set(i, this->get(i) + rhs[i]);
    }
}

void Matrix::operator-=(Matrix &rhs){
   
    Errors::same_dimension(*this, rhs);

    for(std::size_t i = 0; i < this->num_columns(); ++i){
        this->set(i, this->get(i) - rhs[i]);
    }
}

void Matrix::operator*=(Matrix &rhs){

    Errors::same_dimension(*this, rhs);

    if(this->num_columns() != rhs.num_rows()){
        throw std::invalid_argument ("Matrixen sind ned für Multiplickation geigenet");
    }

    for(std::size_t i = 0; i < this->num_rows(); ++i){
        for (std::size_t k = 0; k < rhs.num_columns(); ++k){
            for(std::size_t j = 0; j < rhs.num_rows(); ++j){
                this->get(i).set(j, this->get(i).get(j) * rhs[k][j]);
            }
        }
    }
}