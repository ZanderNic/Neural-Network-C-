#include "lib.h"

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
    auto result = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        result.push_back(this->get(i) - rhs[i]);
    }
    return result;
}

Vector Vector::operator/(Vector &rhs){ 
    auto result = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        result.push_back(this->get(i) - rhs[i]);
    }
    return result;
}

Vector Vector::operator*(Vector &rhs){
    auto result = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        result.push_back(this->get(i) * rhs[i]);
    }
    return result;
}

Vector Vector::operator<(Vector &rhs){
    auto result = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        result.set(i, this->get(i) < rhs[i]);
    }

    return result;
}

Vector Vector::operator>(Vector &rhs){
    auto result = Vector();

    for (std::size_t i = 0; i < this->size(); ++i){
        result.set(i, this->get(i) > rhs[i]);
    }

    return result;
}

void Vector::operator+=(Vector &rhs){
    for (std::size_t i = 0; i < this->size(); ++i){
        auto e = this->get(i) + rhs[i];
        this->set(i, e);
    }
}

void Vector::operator-=(Vector &rhs){
    for (std::size_t i = 0; i < this->size(); ++i){
        auto e = this->get(i) - rhs[i];
        this->set(i, e);
    }
}

void Vector::operator/=(Vector &rhs){
    for (std::size_t i = 0; i < this->size(); ++i){
        auto e = this->get(i) / rhs[i];
        this->set(i, e);
    }
}

void Vector::operator*=(Vector &rhs){
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

Matrix Matrix::operator+(Matrix &rhs){
    //Errors::same_dimension(*this, rhs); 
    auto result = Matrix();
    for(std::size_t i = 0; i < this->num_columns(); ++i){
        const auto e = this->get(i) + rhs.get(i);
        result.push_back(e);
    }

    return result;
}

Matrix Matrix::operator-(Matrix &rhs){
    auto result = Matrix();
    for(std::size_t i = 0; i < this->num_columns(); ++i){
        const auto e = this->get(i) - rhs.get(i);
        result.push_back(e);
    }

    return result;
}

Matrix Matrix::operator*(Matrix &rhs){
    auto result = Matrix();
    //Fehler ding
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
    //Fehler ding 
    for(std::size_t i = 0; i < this->num_columns(); ++i){
        this->set(i, this->get(i) + rhs[i]);
    }
}

void Matrix::operator-=(Matrix &rhs){
   
    //Fehler ding
    for(std::size_t i = 0; i < this->num_columns(); ++i){
        this->set(i, this->get(i) - rhs[i]);
    }
}

void Matrix::operator*=(Matrix &rhs){
    //Fehler ding
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

ActiviationFunctions::ActiviationFunctions(Vector &v, std::string name){
    using ActMap = std::map<std::string, std::function<Vector(Vector &)>>;
    ActMap activation_functions = {{"sigmoid", sigmoid}};
    auto activiation_result = activation_functions[name](v);
}

Vector ActiviationFunctions::sigmoid(Vector &v){
    static const auto e = std::exp(1);
    static auto e_vector = Vector(std::vector<double>(v.size(), e));
    const auto _x = v.neg();
    const auto e_x = e_vector.pow(_x);

    return (1.0 / (1.0 + e_x));
}

Vector ActiviationFunctions::relu(Vector &v){
    auto result = Vector();

    for (std::size_t i = 0; i < v.size(); ++i){
        if (v[i] <= 0){
            result[i] = 0;
        } else{
            result[i] = v[i];
        }
    }

    return result;
}
