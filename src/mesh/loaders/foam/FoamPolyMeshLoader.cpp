#include "FoamPolyMeshLoader.h"

FoamPolyMeshLoader::FoamPolyMeshLoader(std::string meshDir)
    : FoamMeshLoader(meshDir){
    }

void FoamPolyMeshLoader::loadMesh(){
    this->loadPoints();
    this->loadFaces();
    this->loadOwnerNeighbours();
    this->loadBoundaries();
}

FoamPolyMesh FoamPolyMeshLoader::createMesh(){
    return FoamPolyMesh(
        this->points,
        this->faces,
        this->owners,
        this->neighbours,
        this->boundaries
    );
}

void FoamPolyMeshLoader::loadPoints(){

    std::ifstream pointsFile(this->getMeshDir()+"points");

    if (!pointsFile.is_open()){
        std::cerr<<"Error: Unable to open points file."<<std::endl;
        return;
    }

    std::string pointsLine;
    std::string prevPointsLine;
    int numPoints;

    std::vector<std::vector<double>> points;

    bool processPoints;

    // loop to get to start line
    while (std::getline(pointsFile, pointsLine)){
        if (pointsLine == "("){
            processPoints = true;
            break;
        }
        prevPointsLine = pointsLine;
    }

    // convert prevPointsLine to int
    numPoints = std::stoi(prevPointsLine);

    if (processPoints){

        for (int i=0; i<numPoints; i++){

            std::getline(pointsFile, pointsLine);

            std::vector<double> curPoints;

            // get rid of parantheses
            pointsLine = pointsLine.substr(1, pointsLine.size()-2);

            // declare string stream with pointLine (delimeter = " ")
            std::stringstream ss(pointsLine);

            double vertex;

            // loop through vertices in string stream
            while (ss >> vertex){
                curPoints.push_back(vertex);
            }

            points.push_back(curPoints);
        }

    }

    pointsFile.close();

    this->points = points;
}

void FoamPolyMeshLoader::loadOwnerNeighbours(){

    std::vector<int> owners = this->loadScalarFile<int>("owner");

    std::vector<int> neighbours = this->loadScalarFile<int>("neighbour");

    neighbours.resize(owners.size(), -1);

    this->owners = owners;

    this->neighbours = neighbours;

}

void FoamPolyMeshLoader::loadFaces(){

    std::ifstream facesFile(this->getMeshDir()+"faces");

    if (!facesFile.is_open()){
        std::cerr<<"Error: Unable to open faces file."<<std::endl;
        return;
    }

    std::string facesLine;
    std::string prevFacesLine;
    int numFaces;

    std::vector<std::vector<int>> faces;

    bool processFaces;

    // loop to get to start line
    while (std::getline(facesFile, facesLine)){
        if (facesLine == "("){
            processFaces = true;
            break;
        }
        prevFacesLine = facesLine;
    }

    // convert prevPointsLine to int
    numFaces = std::stoi(prevFacesLine);

    if (processFaces){

        for (int i=0; i<numFaces; i++){

            std::getline(facesFile, facesLine);

            std::vector<int> curFaces;

            // get rid of parantheses
            facesLine = facesLine.substr(2, facesLine.size()-3);

            // declare string stream with facesLine (delimeter = " ")
            std::stringstream ss(facesLine);

            int vertex;

            // loop through vertices in string stream
            while (ss >> vertex){
                curFaces.push_back(vertex);
            }

            faces.push_back(curFaces);
        }

    }

    facesFile.close();

    this->faces = faces;
}

void FoamPolyMeshLoader::loadBoundaries(){

    std::ifstream boundariesFile(this->getMeshDir()+"boundary");

    if (!boundariesFile.is_open()){
        std::cerr<<"Error: Unable to open boundary file."<<std::endl;
        return;
    }

    std::string boundariesLine;
    std::string prevBoundariesLine;

    std::vector<BasicBoundary> boundaries;

    // loop to get to start line
    while (std::getline(boundariesFile, boundariesLine)){
        if (boundariesLine == "("){
            break;
        }
    }

    std::string boundary, prevLine, curStream, prevStream, type;
    int numFaces, startFace;

    while (std::getline(boundariesFile, boundariesLine)){

        if (boundariesLine == ")"){
            break;
        }

        // trim leading and trailing whitespace
        size_t firstNonWhitespace = boundariesLine.find_first_not_of(" \t\n\r");
        size_t lastNonWhitespace = boundariesLine.find_last_not_of(" \t\n\r;");
        boundariesLine = boundariesLine.substr(firstNonWhitespace, (lastNonWhitespace - firstNonWhitespace + 1));

        if (boundariesLine == "{"){
            boundary = prevLine;
            continue;
        }
        if (boundariesLine == "}"){
            boundaries.push_back(BasicBoundary(boundary,type,numFaces,startFace));
            continue;
        }

        std::stringstream ss(boundariesLine);

        if (boundariesLine == "{"){
            boundary = prevLine;
        }

        while(ss >> curStream){
            if (prevStream == "type"){
                type = curStream;
            }
            if (prevStream == "nFaces"){
                numFaces = std::stoi(curStream);
            }
            if (prevStream == "startFace"){
                startFace = std::stoi(curStream);
            }
            prevStream = curStream;
        }

        prevLine = boundariesLine;
    }

    this->boundaries = boundaries;

}

template<typename T>
std::vector<T> FoamPolyMeshLoader::loadScalarFile(std::string fileName){

    std::ifstream file(this->getMeshDir()+fileName);

    if (!file.is_open()){
        std::cerr<<"Error: Unable to open "<<fileName<<" file"<<std::endl;
    }

    std::string line;
    std::string prevLine;
    int num;

    std::vector<T> fileVec;

    bool process;

    // loop to get to start line
    while (std::getline(file, line)){
        if (line == "("){
            process = true;
            break;
        }
        prevLine = line;
    }

    // convert prevOwnerLine to int
    num = std::stoi(prevLine);

    if (process){

        for (int i=0; i<num; i++){
            
            // get next line in file
            std::getline(file, line);

            // cast the line to the templated type - might want some error protection here
            std::istringstream iss(line);
            T castLine;
            iss >> castLine;

            // push line into vector
            fileVec.push_back(castLine);
        }
    }

    file.close();

    return fileVec;

}