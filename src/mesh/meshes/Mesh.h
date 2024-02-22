#ifndef MESH_H
#define MESH_H

class Mesh{

    public:

        virtual int numCells() const = 0;

        virtual int numPoints() const = 0;

};

#endif