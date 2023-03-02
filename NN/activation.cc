#include "lib.h"

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
