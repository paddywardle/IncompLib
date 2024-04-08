#ifndef FIELDLOADER_H
#define FIELDLOADER_H

#include <string>

template <typename fieldType, typename meshType>
class FieldLoader{

    public:

        FieldLoader(std::string fieldDir, std::string fieldFile, meshType mesh)
            :fieldDir(fieldDir),fieldFile(fieldFile),mesh(mesh){};

        std::string getFieldDir(){
            return this->fieldDir;
        }

        const meshType& getMesh(){
            return this->mesh;
        }

        virtual void loadField() = 0;

        virtual void loadInternalField() = 0;

        virtual void loadBoundaryField() = 0;

        virtual fieldType createField() const = 0;

    private:

        std::string fieldDir;
        std::string fieldFile;
        meshType mesh;
};

#endif