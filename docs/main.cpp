#include "main.h"

int main(){
    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    std::cout<<meshLoader.getMeshDir()<<"\n";

    meshLoader.loadMesh();

    clock_t start = clock();
    FoamPolyMesh mesh = meshLoader.createMesh();
    clock_t end = clock();
    double duration = static_cast<double>(end-start)/CLOCKS_PER_SEC;
    std::cout<<duration<<"\n";

    std::vector<std::vector<double>> cellCentres = mesh.cellCentres();

}