#ifndef FIELDBOUNDARY_H
#define FIELDBOUNDARY_H

#include <string>

#include "BoundaryTypes.h"

struct FieldBoundary{

    std::string boundary;
    BoundaryType boundaryType;
    double value;

    FieldBoundary(std::string boundary, std::string type, double value=0.0)
        :boundary(boundary),boundaryType(BoundaryType::empty),value(value){};
};

#endif