#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <string>

template <typename meshType>
class MeshLoader{

    // Mesh Loader abstract base class
    public:

        MeshLoader(std::string meshDir)
            :meshDir(meshDir){};

        std::string getMeshDir(){
            return this->meshDir;
        };

        virtual void loadMesh() = 0;

        virtual meshType createMesh() = 0;
        
    private:
    
        std::string meshDir;

};

#endif