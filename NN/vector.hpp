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
    private:
        using vector_ = std::vector<double>;
        vector_ m_backing_vec;
    protected:
    public:
        Vector() = default;
        Vector(vector_ v) : m_backing_vec(std::move(v)){}
        Vector(size_t len, double value = 0.0) : m_backing_vec(len, value){}

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
};

