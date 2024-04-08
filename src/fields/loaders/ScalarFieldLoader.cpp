#include "ScalarFieldLoader.h"

// template<typename meshType>
// ScalarFieldLoader<meshType>::ScalarFieldLoader(std::string fieldDir, std::string fieldFile, meshType mesh)
//     : FieldLoader(fieldDir,fieldFile,mesh){}

// template<typename meshType>
void ScalarFieldLoader::loadInternalField(){

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

void ScalarFieldLoader::loadBoundaryField(){

    // currently just for uniform fields
    std::ifstream fieldFile(this->getFieldDir());

    std::string fieldLine, prevFieldLine, boundary, boundaryType, curStream, prevStream;
    double boundaryValue;

    std::vector<FieldBoundary> fieldBoundaries;

    // loop to get to start line
    while (std::getline(fieldFile, fieldLine)){
        if ((fieldLine == "{") && (prevFieldLine == "boundaryField")){
            break;
        }
        prevFieldLine = fieldLine;
    }

    while (getline(fieldFile, fieldLine)){

        if (fieldLine == "}" && prevFieldLine == "}"){
            break;
        }

        // trim leading and trailing whitespace
        size_t firstNonWhitespace = fieldLine.find_first_not_of(" \t\n\r");
        size_t lastNonWhitespace = fieldLine.find_last_not_of(" \t\r\n");
        fieldLine = fieldLine.substr(firstNonWhitespace, (lastNonWhitespace - firstNonWhitespace + 1));

        if (fieldLine == "{"){
            boundary = prevFieldLine;
            continue;
        }
        if (fieldLine == "}" && boundary.find("|") == std::string::npos){
            fieldBoundaries.push_back(FieldBoundary(boundary,boundaryType, 0.0));
            continue;
        }
        if (fieldLine == "}" && boundary.find("|") != std::string::npos){
            // if multiple boundaries are in the same string
            size_t firstNonBracket = boundary.find_first_not_of("()");
            size_t lastNonBracket = boundary.find_last_not_of("()");
            fieldLine = fieldLine.substr(firstNonWhitespace, (lastNonWhitespace - firstNonWhitespace + 1));
            
            std::string unpackBoundary;
            std::stringstream ss(fieldLine);

            while (std::getline(ss, unpackBoundary, '|')){
                fieldBoundaries.push_back(FieldBoundary(unpackBoundary,boundaryType, 0.0));
            }
            continue;
        }

        std::stringstream ss(fieldLine);

        if (fieldLine == "{"){
            boundary = prevFieldLine;
        }

        while(ss >> curStream){
            if (prevStream == "type"){
                boundaryType = curStream;
            }
            if (prevStream == "value" && curStream == "uniform"){
                ss >> curStream;
                boundaryValue = std::stod(curStream);
            }
            prevStream = curStream;
        }

        prevFieldLine = fieldLine;
    }

    this->fieldBoundaries = fieldBoundaries;

}