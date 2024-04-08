#ifndef SCALARFIELDLOADER_H
#define SCALARFIELDLOADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "FieldLoader.h"
#include "../../mesh/meshes/foam/FoamPolyMesh.h"
#include "../ScalarField.h"
#include "../boundaries/FieldBoundary.h"

// template<typename meshType>
class ScalarFieldLoader : FieldLoader<ScalarField, FoamPolyMesh>{

    public:

        ScalarFieldLoader(std::string fieldDir, std::string fieldFile, FoamPolyMesh mesh)
            : FieldLoader(fieldDir,fieldFile,mesh){}

        void loadField() override;

        void loadInternalField() override;

        void loadBoundaryField() override;

        ScalarField createField() const override;

    private:

        std::vector<double> internalField;
        std::vector<FieldBoundary> fieldBoundaries;

};

// template class ScalarFieldLoader<FoamPolyMesh>;

#endif