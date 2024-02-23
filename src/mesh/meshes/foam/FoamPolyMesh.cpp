#include "FoamPolyMesh.h"

std::vector<std::vector<double>> FoamPolyMesh::faceCentres() const{

    size_t numFaces = this->numFaces();

    std::vector<std::vector<double>> faceCentres(numFaces, {0,0,0});
    const std::vector<std::vector<int>>& faces = this->getFaces();
    const std::vector<std::vector<double>>& points = this->getPoints();

    for (int i=0; i<numFaces; i++) {

        const std::vector<int>& facePoints = faces[i];

        std::vector<double> faceCentre(3,0.0); // all faces will be in 3D

        const int numPoints = facePoints.size();

        for (int j=0; j<numPoints; j++){

            const int& facePoint = facePoints[j];

            const std::vector<double>& point = points[facePoint];
            
            // cbegin and cend == const access
            std::transform(faceCentre.cbegin(), faceCentre.cend(), point.cbegin(), faceCentre.begin(), std::plus<>{});
        }
        std::transform(faceCentre.cbegin(), faceCentre.cend(), faceCentre.begin(), 
                        [&numPoints](double num){return num/numPoints;});

        faceCentres[i] = faceCentre;
    }

    return faceCentres;
}

std::vector<std::vector<double>> FoamPolyMesh::cellCentres() const{

    size_t numCells = this->numCells();
    size_t numFaces = this->numFaces();
    size_t numPoints = this->numPoints();
    
    std::vector<std::vector<double>> cellCentres(numCells+1, {0,0,0});

    const std::vector<int>& owners = this->getOwners();
    const std::vector<int>& neighbours = this->getNeighbours();
    const std::vector<std::vector<int>>& faces = this->getFaces();
    const std::vector<std::vector<double>>& points = this->getPoints();

    std::vector<std::set<int>> cellPoints(numCells+1);

    for (int i=0; i<numFaces; i++){

        const int& owner = owners[i];
        const int& neighbour = neighbours[i];
        const std::vector<int>& facePoints = faces[i];

        const int numPointsInCell = facePoints.size();

        // insert into set to get unique points that make up cell
        for (int j=0; j<numPointsInCell; j++){
            if (neighbour != -1){
                cellPoints[neighbour].insert(facePoints[j]);
            }
            cellPoints[owner].insert(facePoints[j]);
        }
    }

    for (int i=0; i<numCells; i++){

        std::vector<double> cellCentre(3,0.0); // centre is 3D

        const int numPointsInCell = cellPoints[i].size();

        for (const int& cellPoint: cellPoints[i]){

            const std::vector<double>& point = points[cellPoint];

            std::transform(cellCentre.cbegin(), cellCentre.cend(), point.cbegin(), cellCentre.begin(), std::plus<>{});

        }

        std::transform(cellCentre.cbegin(), cellCentre.cend(), cellCentre.begin(),
                        [&numPointsInCell](double num){return num/numPointsInCell;});

        cellCentres[i] = cellCentre;

    }

    return cellCentres;

}

double FoamPolyMesh::tetrahedronVolume(const std::vector<double>& facePoint1, const std::vector<double>& facePoint2, const std::vector<double>& faceCentre, const std::vector<double>& cellCentre) const{

    
    // calculate vectors between points
    std::vector<double> AB = LinAlgOps::ABVec<double>(facePoint1, facePoint2);
    std::vector<double> AC = LinAlgOps::ABVec<double>(facePoint1, faceCentre);
    std::vector<double> AD = LinAlgOps::ABVec<double>(facePoint1, cellCentre);

    // calculate cross product of two vectors
    std::vector<double> crossProd = LinAlgOps::cross<double>(AC, AD);

    // calculate scalar triple product
    double scalarTrip = LinAlgOps::dot<double>(AB, crossProd);

    return std::fabs(scalarTrip) / 6.0;
}

std::vector<double> FoamPolyMesh::cellVolumes() const{

    const int numCells = this->numCells();

    std::vector<double> cellVolumes(numCells+1,0.0);

    const std::vector<std::vector<double>>& faceCentres = this->meshFaceCentres;
    const std::vector<std::vector<double>>& cellCentres = this->meshCellCentres;

    const std::vector<int>& owners = this->getOwners();
    const std::vector<int>& neighbours = this->getNeighbours();

    const std::vector<std::vector<double>>& points = this->getPoints();
    const std::vector<std::vector<int>>& faces = this->getFaces();

    const int numOwners = owners.size();

    // initialise here to avoid repeated initialisation
    int jPlus1, facePoint, facePointPlus1;

    for (int i=0; i<numOwners; i++){

        const int& owner = owners[i];
        const int& neighbour = neighbours[i];

        const std::vector<int>& face = faces[i];
        const std::vector<double>& ownerCentre = cellCentres[owner];
        const std::vector<double>& neighbourCentre = cellCentres[neighbour];
        const std::vector<double>& faceCentre = faceCentres[i];

        const int numPointsInFace = face.size();

        for (int j=0; j<numPointsInFace; j++){
            
            // if at the end of the vec use first element
            jPlus1 = (j+1)%numPointsInFace;

            facePoint = face[j];
            facePointPlus1 = face[jPlus1];

            cellVolumes[owner] += this->tetrahedronVolume(points[facePoint], points[facePointPlus1], faceCentre, ownerCentre);

            if (neighbour != -1){
                cellVolumes[neighbour] += this->tetrahedronVolume(points[facePoint], points[facePointPlus1], faceCentre, neighbourCentre);
            }
        }
    }
    return cellVolumes;

}