#pragma once

#include <vector>
#include <iostream>
#include <cstddef> // std::size_t
#include <cstdint>
#include <string>
#include <map>
#include <functional> // std::function
#include <cmath> // std::exp

class Vector{
    protected:
    public:
        using vector_ = std::vector<double>;

        Vector() = default;
        Vector(vector_ v) : m_backing_vec{std::move(v)}{}

        std::size_t size() const {return m_backing_vec.size();}
        double get(std::size_t index) const {return m_backing_vec[index];}
        void set(std::size_t index, double element) {m_backing_vec[index] = element;}
        double &operator[](const std::size_t index) {return m_backing_vec[index];}
        void push_back(double element){m_backing_vec.push_back(element);}
        void pop_back(){m_backing_vec.pop_back();}
        Vector neg();
        Vector pow(int exp);
        Vector pow(const Vector &exp) const;
        Vector operator+(Vector &rhs);
        Vector operator-(Vector &rhs);
        Vector operator/(Vector &rhs);
        Vector operator*(Vector &rhs);
        Vector operator<(Vector &rhs);
        Vector operator>(Vector &rhs);
        friend Vector operator+(const double lhs, const Vector &rhs){
            auto result = Vector();

            for (std::size_t i = 0; i < rhs.size(); ++i){
                auto e = lhs + rhs.get(i);
                result.set(i, e);
            }

            return result;
        }

        friend Vector operator-(double lhs, Vector &rhs){
            auto result = Vector();

            for (std::size_t i = 0; i < rhs.size(); ++i){
                auto e = lhs - rhs[i];
                result.set(i, e);
            }

            return result;
        }

        friend Vector operator*(const double lhs, const Vector &rhs){
            auto result = Vector();

            for (std::size_t i = 0; i < rhs.size(); ++i){
                auto e = lhs * rhs.get(i);
                result.set(i, e);
            }

            return result;
        }

        friend Vector operator/(const double lhs, const Vector &rhs){
            auto result = Vector();

            for (std::size_t i = 0; i < rhs.size(); ++i){
                auto e = lhs - rhs.get(i);
                result.set(i, e);
            }

            return result;
        }

        friend Vector operator<(double lhs, Vector &rhs){
            auto result = Vector();

            for (std::size_t i = 0; i < rhs.size(); ++i){
                result.set(i, lhs < rhs[i]);
            }

            return result;
        }

        friend Vector operator>(double lhs, Vector &rhs){
            auto result = Vector();

            for (std::size_t i = 0; i < rhs.size(); ++i){
                result.set(i, lhs > rhs[i]);
            }

            return result;
        }

        void operator+=(Vector &rhs);
        void operator-=(Vector &rhs);
        void operator/=(Vector &rhs);
        void operator*=(Vector &rhs);
        friend std::ostream& operator<<(std::ostream& os, const Vector& v){
            os << "(";
            for (std::size_t i = 0; i < v.size() - 1; ++i){
                os << v.get(i) << "," << std::endl;
            }
            os << v.get(v.size() - 1) << ")";

            return os;
        }
        ~Vector() = default;

    private:
        vector_ m_backing_vec;
};

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

class ActiviationFunctions{
    private:
    protected:
    public:
        ActiviationFunctions() = default;
        ActiviationFunctions(Vector &v, std::string name="sigmoid");
        static Vector sigmoid(Vector &v);
        static Vector relu(Vector &v);
        ~ActiviationFunctions() = default;
};

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