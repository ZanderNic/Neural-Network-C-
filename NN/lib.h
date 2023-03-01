#pragma once

#include <vector>
#include <iostream>
#include <cstddef> // size_t
#include <cstdint>
#include <string>
#include <map>
#include <functional> // std::function
#include <cmath> // std::exp

namespace Errors{
    template<typename T>
    void same_dimension(){}
}

class Vector{
    protected:
    public:
        using vector_ = std::vector<double>;

        Vector() = default;
        Vector(vector_ p) : m_backing_vec{std::move(p)}{}

        size_t size = m_backing_vec.size();
        double get(size_t index) const {return m_backing_vec[index];}
        void set(size_t index, double element) {m_backing_vec[index] = element;}
        double operator[](size_t index) const {return m_backing_vec[index];}
        void push_back(double element){m_backing_vec.push_back(element);}
        void pop_back(){m_backing_vec.pop_back();}
        Vector neg();
        Vector pow(int exp);
        Vector pow(Vector &exp);
        Vector operator+(Vector &rhs);
        Vector operator-(Vector &rhs);
        Vector operator/(Vector &rhs);
        Vector operator*(Vector &rhs);
        friend Vector operator+(double lhs, Vector &rhs){
            auto result = Vector();
            for (size_t i = 0; i < rhs.size; ++i){
                auto e = lhs + rhs[i];
                result.set(i, e);
            }

            return result;
        }

        friend Vector operator-(double lhs, Vector &rhs){
            auto result = Vector();
            for (size_t i = 0; i < rhs.size; ++i){
                auto e = lhs - rhs[i];
                result.set(i, e);
            }

            return result;
        }

        friend Vector operator*(double lhs, Vector &rhs){
            auto result = Vector();
            for (size_t i = 0; i < rhs.size; ++i){
                auto e = lhs * rhs[i];
                result.set(i, e);
            }

            return result;
        }

        friend Vector operator/(double lhs, Vector &rhs){
            auto result = Vector();
            for (size_t i = 0; i < rhs.size; ++i){
                auto e = lhs - rhs[i];
                result.set(i, e);
            }

            return result;
        }

        void operator+=(Vector &rhs);
        void operator-=(Vector &rhs);
        void operator/=(Vector &rhs);
        void operator*=(Vector &rhs);
        Vector operator=(Vector &rhs);
        friend std::ostream& operator<<(std::ostream& os, const Vector& p);
        ~Vector() = default;

    private:
        vector_ m_backing_vec;
};

Vector Vector::operator+(Vector &rhs){
    auto result = Vector();

    for (size_t i = 0; i < this->size; ++i){
        result.push_back(this->get(i) + rhs[i]);
    }

    return result;
}

Vector Vector::operator-(Vector &rhs){
    auto result = Vector();

    for (size_t i = 0; i < this->size; ++i){
        result.push_back(this->get(i) - rhs[i]);
    }
    return result;
}

Vector Vector::operator/(Vector &rhs){ 
    auto result = Vector();

    for (size_t i = 0; i < this->size; ++i){
        result.push_back(this->get(i) - rhs[i]);
    }
    return result;
}

Vector Vector::operator*(Vector &rhs){
    auto result = Vector();

    for (size_t i = 0; i < this->size; ++i){
        result.push_back(this->get(i) * rhs[i]);
    }
    return result;
}

void Vector::operator+=(Vector &rhs){
    for (size_t i = 0; i < this->size; ++i){
        auto e = this->get(i) + rhs[i];
        this->set(i, e);
    }
}

void Vector::operator-=(Vector &rhs){
    for (size_t i = 0; i < this->size; ++i){
        auto e = this->get(i) - rhs[i];
        this->set(i, e);
    }
}

void Vector::operator/=(Vector &rhs){
    for (size_t i = 0; i < this->size; ++i){
        auto e = this->get(i) / rhs[i];
        this->set(i, e);
    }
}

void Vector::operator*=(Vector &rhs){
    for (size_t i = 0; i < this->size; ++i){
        auto e = this->get(i) - rhs[i];
        this->set(i, e);
    }
}

std::ostream& operator<<(std::ostream& os, const Vector& p){
    os << "(";
    for (size_t i = 0; i < p.size - 1; ++i){
        os << p[i] << ",";
    }
    os << p.get(p.size - 1) << ")";

    return os;
}

Vector Vector::neg(){
    Vector result = Vector();
    
    for (size_t i = 0; i < this->size; ++i){
        result.set(i, -this->get(i));
    }

    return result;
}

Vector Vector::pow(const int exp){
    Vector result = Vector();
    
    for (size_t i = 0; i < this->size; ++i){
        result.set(i, std::pow(this->get(i), exp));
    }

    return result;
}

Vector Vector::pow(Vector &exp){
    Vector result = Vector();
    
    for (size_t i = 0; i < this->size; ++i){
        result.set(i, std::pow(this->get(i), exp.get(i)));
    }

    return result;
}

class Matrix : Vector{
    
    protected:
    public:
        using matrix = std::vector<Vector>;
        Matrix() = default;
        Matrix(matrix p):m_backing_matrix{std::move(p)}{}
        
        Matrix operator-(Matrix &rhs);
        Matrix operator+(Matrix &rhs);
        Matrix operator*(Matrix &rhs);
        Matrix operator/(Matrix &rhs);
        size_t num_columns = m_backing_matrix.size();
        size_t num_rows = m_backing_matrix[0].size;
        Vector& operator[](size_t index){return m_backing_matrix[index];}
        void operator+=(Matrix &rhs);      
        void operator-=(Matrix &rhs);
        void operator*=(Matrix &rhs);
        void operator/=(Matrix &rhs);
        Vector& get(size_t index){return m_backing_matrix[index];}
        void set(size_t index, Vector element){m_backing_matrix[index] = element;}
        void push_back(Vector element){m_backing_matrix.push_back(element);}
        void pop_back(){m_backing_matrix.pop_back();}
        
        ~Matrix() = default;
    
    private:
        matrix m_backing_matrix;
};

Matrix Matrix::operator+(Matrix &rhs){
    auto result = Matrix();
    for(size_t i = 0; i < this->num_columns; ++i){
        const auto e = this->get(i) + rhs.get(i);
        result.push_back(e);
    }

    return result;
}

Matrix Matrix::operator-(Matrix &rhs){
    
    //Error Größe

    auto result = Matrix();
    for(size_t i = 0; i < this->num_columns; ++i){
        const auto e = this->get(i) - rhs.get(i);
        result.push_back(e);
    }

    return result;
}

Matrix Matrix::operator*(Matrix &rhs){
    auto result = Matrix();
    //Fehler ding
    if(this->num_columns != rhs.num_rows){
        throw std::invalid_argument ("Matrixen sind ned für Multiplickation geigenet");
    }

    for(size_t i = 0; i < this->num_rows; ++i){
        for (size_t k = 0; k < rhs.num_columns; ++k){
            for(size_t j = 0; j < rhs.num_rows; ++j){
                result[i].set(j, result[i][j] * rhs[i][j]);
            }
        }
    }
    return result;
};


void Matrix::operator+=(Matrix &rhs){
    //Fehler ding 
    for(size_t i = 0; i < this->num_columns; ++i){
        this->set(i, this->get(i) + rhs[i]);
    }
}

void Matrix::operator-=(Matrix &rhs){
   
    //Fehler ding
    for(size_t i = 0; i < this->num_columns; ++i){
        this->set(i, this->get(i) - rhs[i]);
    }
}

void Matrix::operator*=(Matrix &rhs){
    //Fehler ding
    if(this->num_columns != rhs.num_rows){
        throw std::invalid_argument ("Matrixen sind ned für Multiplickation geigenet");
    }

    for(size_t i = 0; i < this->num_rows; ++i){
        for (size_t k = 0; k < rhs.num_columns; ++k){
            for(size_t j = 0; j < rhs.num_rows; ++j){
                this->get(i).set(j, this->get(i).get(j) * rhs[k][j]);
            }
        }
    }
}

class ActiviationFunctions{
    private:
    protected:
    public:
        ActiviationFunctions() = default;
        ActiviationFunctions(Vector &v, std::string name="sigmoid");
        Vector sigmoid(Vector &v);
        void testFunc1() {
            puts("func2");
        }
        ~ActiviationFunctions() = default;
};

ActiviationFunctions::ActiviationFunctions(Vector &v, std::string name){
    using ActMap = std::map<std::string, std::function<Vector(Vector &)>>;
    ActMap activation_functions = {{"sigmoid", sigmoid}};

    auto activiation_result = activation_functions[name](v);
}

Vector ActiviationFunctions::sigmoid(Vector &v){
    auto e = std::exp(1);
    auto e_vector = Vector(std::vector<double>(v.size, e));
    auto _x = v.neg();
    const auto e_x = e_vector.pow(_x);
    return (1.0 / (1.0 + e_x));
}
