#ifndef LINALGOPS_H
#define LINALGOPS_H

#include <vector>

#include "LinAlgExceptions.h"

namespace LinAlgOps{

    template<typename T>
    T dot(const std::vector<T> vec1, const std::vector<T> vec2);

    template<typename T>
    std::vector<T> cross(const std::vector<T> vec1, const std::vector<T> vec2);

    template<typename T>
    std::vector<T> ABVec(const std::vector<T> A, const std::vector<T> B);

};

#endif