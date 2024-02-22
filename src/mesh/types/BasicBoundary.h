#ifndef BASICBOUNDARY_H
#define BASICBOUNDARY_H

#include <string>

struct BasicBoundary{

    std::string boundary;
    std::string boundaryType;
    int numFaces;
    int startFace;

    BasicBoundary(std::string boundary, std::string type, int numFaces, int startFace)
        :boundary(boundary),boundaryType(type),numFaces(numFaces),startFace(startFace){};
};

#endif