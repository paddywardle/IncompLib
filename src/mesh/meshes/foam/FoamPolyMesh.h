#ifndef FOAMPOLYMESH_H
#define FOAMPOLYMESH_H

#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

#include "FoamMesh.h"
#include "../../types/BasicBoundary.h"
#include "../../../linAlg/LinAlgOps.h"

class FoamPolyMesh : public FoamMesh<BasicBoundary>{

    public:

        FoamPolyMesh(std::vector<std::vector<double>> points, 
                     std::vector<std::vector<int>> faces, 
                     std::vector<int> owners, 
                     std::vector<int> neighbours,
                     std::vector<BasicBoundary> boundaries)
                     :FoamMesh{points, faces, owners, neighbours, boundaries}{

            meshFaceCentres = this->faceCentres();
            meshCellCentres = this->cellCentres();

        };

        std::vector<std::vector<double>> faceCentres() const override;
        std::vector<std::vector<double>> cellCentres() const override;
        std::vector<double> cellVolumes() const override;
        std::vector<double> boundaryFaces() const override{};
        std::vector<double> faceAreaVectors() const override{};

        double tetrahedronVolume(const std::vector<double>& facePoint1, const std::vector<double>& facePoint2, const std::vector<double>& faceCentre, const std::vector<double>& cellCentre) const;

        const std::vector<std::vector<double>>& getFaceCentres(){
            return this->meshFaceCentres;
        }

        const std::vector<std::vector<double>>& getCellCentres(){
            return this->meshCellCentres;
        }

    private:

        // calculate and store face and cell centres - return const references to them
        std::vector<std::vector<double>> meshFaceCentres;
        std::vector<std::vector<double>> meshCellCentres;

};

#endif