#pragma once

#include "vector.hpp"

class Matrix : public Vector{
    
    protected:
    public:
        using matrix = std::vector<Vector>;
        Matrix() = default;
        Matrix(matrix p):m_backing_matrix{std::move(p)}{}
        
        Matrix operator-(Matrix &rhs);
        Matrix operator+(Matrix &rhs);
        Matrix operator*(Matrix &rhs);
        Matrix operator/(Matrix &rhs);
        std::size_t num_columns(){return m_backing_matrix.size();}
        std::size_t num_rows(){return m_backing_matrix[0].size();}
        Vector& operator[](std::size_t index){return m_backing_matrix[index];}
        void operator+=(Matrix &rhs);      
        void operator-=(Matrix &rhs);
        void operator*=(Matrix &rhs);
        void operator/=(Matrix &rhs);
        Vector& get(std::size_t index){return m_backing_matrix[index];}
        void set(std::size_t index, Vector element){m_backing_matrix[index] = element;}
        void push_back(Vector element){m_backing_matrix.push_back(element);}
        void pop_back(){m_backing_matrix.pop_back();}
        
        ~Matrix() = default;
    
    private:
        matrix m_backing_matrix;
};
