#include <functional>
#include <map>

class ActiviationFunctions{
    private:
    protected:
    public:
        ActiviationFunctions() = delete;
        ActiviationFunctions(Vector &v, std::string name="sigmoid");
        Vector sigmoid(Vector &v);
        void testFunc1() {
            puts("func2");
        }
        ~ActiviationFunctions() = default;
};

ActiviationFunctions::ActiviationFunctions(Vector &v, std::string name){
    std::map<std::string, int> m = {{"hallo", 1}};

    using MapType = std::map<int, std::function<void()>>;
    MapType activation_functions = {{1, testFunc1},};


    
    auto activiation_result = activation_functions[name](v);
}

Vector ActiviationFunctions::sigmoid(Vector &v){
    auto e = std::exp(1);
    auto e_vector = Vector(std::vector<double>(v.size, e));
    auto _x = v.neg();
    return (1.0 / (1.0 + e_vector.pow(_x)));
}
