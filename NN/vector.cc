#include <vector.hpp>
#include <errors.hpp>

Vector Vector::operator+(Vector &rhs){

    Errors::same_dimension(*this, rhs);

    std::cout << rhs.size();
    auto result = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        result.push_back(this->get(i) + rhs[i]);
    }

    return result;
}

Vector Vector::operator-(Vector &rhs){

    Errors::same_dimension(*this, rhs);

    auto result = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        result.push_back(this->get(i) - rhs[i]);
    }
    return result;
}

Vector Vector::operator/(Vector &rhs){ 

    Errors::same_dimension(*this, rhs);

    auto result = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        result.push_back(this->get(i) - rhs[i]);
    }
    return result;
}

Vector Vector::operator*(Vector &rhs){

    Errors::same_dimension(*this, rhs);

    auto result = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        result.push_back(this->get(i) * rhs[i]);
    }
    return result;
}

Vector Vector::operator<(Vector &rhs){

    Errors::same_dimension(*this, rhs);

    auto mask = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        mask.set(i, this->get(i) < rhs[i]);
    }

    return mask;
}

Vector Vector::operator>(Vector &rhs){

    Errors::same_dimension(*this, rhs);

    auto mask = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        mask.set(i, this->get(i) > rhs[i]);
    }

    return mask;
}

void Vector::operator+=(Vector &rhs){

    Errors::same_dimension(*this, rhs);

    for (std::size_t i = 0; i < this->size(); ++i){
        auto e = this->get(i) + rhs[i];
        this->set(i, e);
    }
}

void Vector::operator-=(Vector &rhs){

    Errors::same_dimension(*this, rhs);

    for (std::size_t i = 0; i < this->size(); ++i){
        auto e = this->get(i) - rhs[i];
        this->set(i, e);
    }
}

void Vector::operator/=(Vector &rhs){

    Errors::same_dimension(*this, rhs);

    for (std::size_t i = 0; i < this->size(); ++i){
        auto e = this->get(i) / rhs[i];
        this->set(i, e);
    }
}

void Vector::operator*=(Vector &rhs){

    Errors::same_dimension(*this, rhs);

    for (std::size_t i = 0; i < this->size(); ++i){
        auto e = this->get(i) - rhs[i];
        this->set(i, e);
    }
}

Vector Vector::neg(){
    Vector result = Vector();
    
    for (std::size_t i = 0; i < this->size(); ++i){
        result.set(i, -this->get(i));
    }

    return result;
}

Vector Vector::pow(const int exp){
    Vector result = Vector();
    
    for (std::size_t i = 0; i < this->size(); ++i){
        result.set(i, std::pow(this->get(i), exp));
    }

    return result;
}

Vector Vector::pow(const Vector &exp) const{
    Vector result = Vector();
    
    for (std::size_t i = 0; i < this->size(); ++i){
        result.set(i, std::pow(this->get(i), exp.get(i)));
    }

    return result;
}