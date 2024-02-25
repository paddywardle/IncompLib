#ifndef FIELD_H
#define FIELD_H

#include <vector>

template<typename T>
class Field{

    public:
        
        const std::vector<T>& getField(){
            return this->field;
        }

    private:

        std::vector<T> field;
};

// define template options so logic can be in .cpp file
template class Field<std::vector<double>>;
template class Field<std::vector<float>>;
template class Field<std::vector<int>>;
template class Field<double>;
template class Field<float>;
template class Field<int>;

#endif