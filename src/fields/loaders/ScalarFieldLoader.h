#ifndef SCALARFIELDLOADER_H
#define SCALARFIELDLOADER_H

#include "FieldLoader.h"
#include "../../mesh/meshes/foam/FoamPolyMesh.h"
#include "../ScalarField.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// template<typename meshType>
class ScalarFieldLoader : FieldLoader<ScalarField, FoamPolyMesh>{

    public:

        ScalarFieldLoader(std::string fieldDir, std::string fieldFile, FoamPolyMesh mesh)
            : FieldLoader(fieldDir,fieldFile,mesh){}

        void loadField() override;

        ScalarField createField() const override;

    private:

        std::vector<double> internalField;

};

// template class ScalarFieldLoader<FoamPolyMesh>;

#endif