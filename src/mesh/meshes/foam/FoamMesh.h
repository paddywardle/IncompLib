#ifndef FOAMMESH_H
#define FOAMMESH_H

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

#include "../Mesh.h"
#include "../../types/BasicBoundary.h"

// need implementation of templated class in header file (or instantiate specific specialisations)
// this is because when cpp sees an implementation of a templated class it creates an instance of that class based on the header file
// so it needs the implementation there
template<typename boundary>
class FoamMesh : public Mesh{

    public:

        FoamMesh(std::vector<std::vector<double>> points,
                     std::vector<std::vector<int>> faces,
                     std::vector<int> owners,
                     std::vector<int> neighbours,
                     std::vector<boundary> boundaries)
                     :points(points),faces(faces),owners(owners),neighbours(neighbours),boundaries(boundaries){};

        // Virtual Functions
        virtual std::vector<std::vector<double>> faceCentres() const = 0;
        virtual std::vector<std::vector<double>> cellCentres() const = 0;
        virtual std::vector<std::vector<double>> faceAreaVectors() const = 0;
        virtual std::vector<double> cellVolumes() const = 0;
        virtual std::vector<double> boundaryFaces() const = 0;
        
        // Access functions - return const references
        const std::vector<std::vector<double>>& getPoints() const{
            return this->points;
        };

        const std::vector<std::vector<int>>& getFaces() const{
            return this->faces;
        };

        const std::vector<int>& getOwners() const{
            return this->owners;
        };

        const std::vector<int>& getNeighbours() const{
            return this->neighbours;
        };

        // should inherit from a base method and this should be templated for different types of boundaries
        const std::vector<boundary>& getBoundaries() const{
            return this->boundaries;
        };

        int numCells() const override{

            // *std::max_element to deference the pointer to the max element in the vector
            return *std::max_element(this->owners.begin(), this->owners.end());
        };

        int numPoints() const override{
            return this->points.size();
        };

        int numFaces() const{
            return this->faces.size();
        };

    private:

        std::vector<std::vector<double>> points;
        std::vector<std::vector<int>> faces;
        std::vector<int> owners;
        std::vector<int> neighbours;
        std::vector<boundary> boundaries;

};

#endif