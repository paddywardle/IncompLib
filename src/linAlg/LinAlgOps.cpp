#include "LinAlgOps.h"

namespace LinAlgOps{

    template<typename T>
    T dot(const std::vector<T> vec1, const std::vector<T> vec2){

        // should throw error here if they're not the same size

        const int n1 = vec1.size();
        const int n2 = vec2.size();

        if (n1 != n2){
            throw LinAlgExceptions("Vector dimensions do not match!");
        }

        T res = 0;

        for (int i=0; i<n1; i++){
            res += vec1[i] * vec2[i];
        }

        return res;
        
    }

    template<typename T>
    std::vector<T> cross(const std::vector<T> vec1, const std::vector<T> vec2){

        // should throw error here if they're not the same size

        const int n1 = vec1.size();
        const int n2 = vec2.size();

        if (n1 != n2){
            throw LinAlgExceptions("Vector dimensions do not match!");
        }

        // cross product is only in 3D
        std::vector<T> crossProduct(3, 0);

        crossProduct[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
        crossProduct[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
        crossProduct[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

        return crossProduct;
        
    }

    template<typename T>
    std::vector<T> ABVec(const std::vector<T> A, const std::vector<T> B){
        
        const int n1 = A.size();
        const int n2 = B.size();

        if (n1 != n2){
            throw LinAlgExceptions("Vector dimensions do not match!");
        }

        std::vector<T> AB(n1, 0);

        for (int i=0; i<n1; i++){
            AB[i] = A[i] - B[i];
        }

        return AB;

    }

};

template double LinAlgOps::dot<double>(const std::vector<double> A, const std::vector<double> B);
template int LinAlgOps::dot<int>(const std::vector<int> A, const std::vector<int> B);

template std::vector<double> LinAlgOps::cross<double>(const std::vector<double> A, const std::vector<double> B);
template std::vector<int> LinAlgOps::cross<int>(const std::vector<int> A, const std::vector<int> B);

template std::vector<double> LinAlgOps::ABVec<double>(const std::vector<double> A, const std::vector<double> B);
template std::vector<int> LinAlgOps::ABVec<int>(const std::vector<int> A, const std::vector<int> B);