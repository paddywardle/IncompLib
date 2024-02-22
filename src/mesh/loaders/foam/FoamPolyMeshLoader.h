#ifndef FoamPolyMeshLoader_H
#define FoamPolyMeshLoader_H

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "FoamMeshLoader.h"
#include "../../types/BasicBoundary.h"
#include "../../meshes/foam/FoamPolyMesh.h"

class FoamPolyMeshLoader : public FoamMeshLoader<FoamPolyMesh>{

    // this loads in mesh files in the form of an OpenFOAM mesh (blockMesh)

    public:

        FoamPolyMeshLoader(std::string meshDir);

        // overriding implementation form MeshLoader ABC
        void loadMesh() override;

        // this should be templated for different mesh types
        FoamPolyMesh createMesh() override;

    private:

        std::vector<std::vector<double>> points;

        std::vector<std::vector<int>> faces;

        std::vector<int> owners;

        std::vector<int> neighbours;

        std::vector<BasicBoundary> boundaries;
    
        void loadPoints() override;

        void loadOwnerNeighbours() override;

        void loadFaces() override;

        void loadBoundaries() override;

        template<typename T>
        std::vector<T> loadScalarFile(std::string fileName);
};

#endif