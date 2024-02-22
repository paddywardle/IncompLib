#ifndef FOAMMESHLOADER_H
#define FOAMMESHLOADER_H

#include <string>
#include <fstream>

#include "../MeshLoader.h"

template <typename meshType>
class FoamMeshLoader : public MeshLoader<meshType>{

    // this loads in mesh files in the form of an OpenFOAM mesh (blockMesh)

    public:

        FoamMeshLoader(std::string meshDir)
            : MeshLoader<meshType>(meshDir){};

    private:
    
        virtual void loadPoints() = 0;

        virtual void loadOwnerNeighbours() = 0;

        virtual void loadFaces() = 0;

        virtual void loadBoundaries() = 0;
              
};

#endif