#ifndef BOUNDARYTYPES_H
#define BOUNDARYTYPES_H

enum class BoundaryType{
    zeroGradient,
    symmetryPlane,
    fixedValue,
    noSlip,
    empty
};

#endif