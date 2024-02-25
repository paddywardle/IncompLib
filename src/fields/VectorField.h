#ifndef VECTORFIELD_H
#define VECTORFIELD_H

#include <vector>

#include "Field.h"

template <typename T>
class VectorField : Field<std::vector<T>>{

};

// define template options so logic can be in .cpp file
template class VectorField<double>;
template class VectorField<float>;
template class VectorField<int>;

#endif