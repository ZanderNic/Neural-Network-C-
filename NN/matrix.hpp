#pragma once

#include "vector.hpp"

class Matrix : public Vector{
    private:
        using matrix_ = std::vector<Vector>;
        matrix_ m_backing_matrix;
    protected:
    public:
        Matrix() = default;
        Matrix(size_t num_rows, size_t num_cols) : m_backing_matrix(num_cols, Vector(num_rows)){}
        Matrix(matrix_ m) : m_backing_matrix(std::move(m)){}

        Matrix operator-(Matrix &rhs);
        Matrix operator+(Matrix &rhs);
        Matrix operator*(Matrix &rhs);
        std::size_t num_columns() const {return m_backing_matrix.size();}
        std::size_t num_rows() const {return m_backing_matrix[0].size();}
        Vector& operator[](const std::size_t index) {
            
            for (size_t i = 0; i < this->num_columns(); ++i){
                m_backing_matrix[index];}
        void operator+=(Matrix &rhs);
        void operator-=(Matrix &rhs);
        void operator*=(Matrix &rhs);
        Vector& get(const std::size_t index) {return m_backing_matrix[index];}
        void set(std::size_t index, Vector element){m_backing_matrix[index] = element;}
        void push_back(Vector element){m_backing_matrix.push_back(element);}
        void pop_back(){m_backing_matrix.pop_back();}
        friend std::ostream& operator<<(std::ostream& os, const Matrix &ma){        
            for (size_t m = 0; m < ma.num_rows(); ++m){
               for(size_t n = 0; n < ma.num_columns(); ++n){
                    os << ma.m_backing_matrix[m].get(n) << "  ";
                }
               os << std::endl;
            }

            return os;
        }
        
        ~Matrix() = default;

};