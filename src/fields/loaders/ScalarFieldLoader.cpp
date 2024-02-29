#include "ScalarFieldLoader.h"

// template<typename meshType>
// ScalarFieldLoader<meshType>::ScalarFieldLoader(std::string fieldDir, std::string fieldFile, meshType mesh)
//     : FieldLoader(fieldDir,fieldFile,mesh){}

// template<typename meshType>
void ScalarFieldLoader::loadField(){

    // currently just for uniform fields
    std::ifstream fieldFile(this->getFieldDir());

    std::string fieldLine;

    size_t firstNonWhitespace,lastNonWhitespace;
    std::string curStream, prevStream;
    double internalFieldVal;

    while(std::getline(fieldFile, fieldLine)){

        // trim whitespace
        firstNonWhitespace = fieldLine.find_first_not_of(" \t\r\n");
        lastNonWhitespace = fieldLine.find_last_not_of(" \t\r\n");
        fieldLine = fieldLine.substr(firstNonWhitespace,(lastNonWhitespace-firstNonWhitespace+1));

        std::stringstream ss(fieldLine); // can be either i or o depending on << or >>
        ss >> curStream; // get first ss

        if (curStream != "internal"){
            continue;
        }

        while(ss >> curStream){
            if (prevStream == "uniform"){
                internalFieldVal = std::stod(curStream); // convert string to double
            }
            prevStream = curStream;
        }
    }

    const int numCells = this->getMesh().numCells();

    this->internalField = std::vector<double>(numCells+1,internalFieldVal);

}