#include <gtest/gtest.h>
#include <string>
#include <iostream>

#include "../../../../src/mesh/loaders/foam/FoamPolyMeshLoader.h"
#include "../../../../src/mesh/meshes/foam/FoamPolyMesh.h"

TEST(FoamPolyMeshLoaderTests, meshDir){

    FoamPolyMeshLoader meshLoader("dir");

    std::string meshDir = meshLoader.getMeshDir();

    EXPECT_EQ(meshDir, "dir");
}

TEST(FoamPolyMeshLoaderTests, loadPoints){

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<std::vector<double>> points = mesh.getPoints();

    EXPECT_EQ(points[0][1], -0.0005);

}

TEST(FoamPolyMeshLoaderTests, loadFaces){

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<std::vector<int>> faces = mesh.getFaces();

    EXPECT_EQ(faces[0][1], 42);
    EXPECT_EQ(faces[3][2], 904);

}

TEST(FoamPolyMeshLoaderTests, loadOwners){

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<int> owners = mesh.getOwners();

    EXPECT_EQ(owners[0], 0);
    EXPECT_EQ(owners[3], 1);

}

TEST(FoamPolyMeshLoaderTests, loadNeighbours){

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<int> neighbours = mesh.getNeighbours();

    EXPECT_EQ(neighbours[0], 1);
    EXPECT_EQ(neighbours[3], 41);

}

TEST(FoamPolyMeshLoaderTests, loadBoundaries){

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<BasicBoundary> boundaries = mesh.getBoundaries();

    EXPECT_EQ(boundaries[0].boundary, "inlet");
    EXPECT_EQ(boundaries[0].boundaryType, "patch");
    EXPECT_EQ(boundaries[0].numFaces, 20);
    EXPECT_EQ(boundaries[0].startFace, 9420);

}

TEST(FoamPolyMeshLoaderTests, faceCentres){

    // implement this test

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<std::vector<double>> faceCentres = mesh.faceCentres();

    std::vector<double> faceCentre = faceCentres[0];

    EXPECT_NEAR(faceCentre[0],1.7311045e-05, 0.0001);
    EXPECT_NEAR(faceCentre[1],-4.8750000e-04, 0.0001);
    EXPECT_NEAR(faceCentre[2],1.2500000e-04, 0.0001);

}

TEST(FoamPolyMeshLoaderTests, cellCentres){

    // implement this test

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<std::vector<double>> cellCentres = mesh.cellCentres();

    std::vector<double> cellCentre = cellCentres[0];

    EXPECT_NEAR(cellCentre[0],8.65552251e-06, 0.0001);
    EXPECT_NEAR(cellCentre[1],-4.87500000e-04, 0.0001);
    EXPECT_NEAR(cellCentre[2],1.2500000e-04, 0.0001);

}

TEST(FoamPolyMeshLoaderTests, tetrahedronVolume){

    // implement this test

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<double> facePoint1 = {0.00032973, -0.000475, 0.0};
    std::vector<double> facePoint2 = {0.00032973, -0.00045, 0.0};
    std::vector<double> faceCentre = {0.00032973, -0.0004625, 0.000125};
    std::vector<double> cellCentre = {0.00032388, -0.0004625, 0.000125};

    double tetVolume = mesh.tetrahedronVolume(facePoint1, facePoint2, faceCentre, cellCentre);

    EXPECT_NEAR(tetVolume,3.0491603906249936e-15, 1e-17);

}

TEST(FoamPolyMeshLoaderTests, tetrahedronVolume2){

    // implement this test

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<double> facePoint1 = {0.0,-0.000475,0.00025};
    std::vector<double> facePoint2 = {1.7311045e-05,-4.7500000e-04,2.5000000e-04};
    std::vector<double> faceCentre = {8.65552251e-06,-4.75000000e-04,1.25000000e-04};
    std::vector<double> cellCentre = {8.65552251e-06,-4.87500000e-04,1.25000000e-04};

    double tetVolume = mesh.tetrahedronVolume(facePoint1, facePoint2, faceCentre, cellCentre);

    EXPECT_NEAR(tetVolume,4.508084640625008e-15, 1e-19);

}

TEST(FoamPolyMeshLoaderTests, cellVolume){

    // implement this test

    FoamPolyMeshLoader meshLoader("../mesh_files/backward_step/");

    meshLoader.loadMesh();

    FoamPolyMesh mesh = meshLoader.createMesh();

    std::vector<double> cellVolumes = mesh.cellVolumes();

    double cellVol = cellVolumes[0];

    EXPECT_NEAR(cellVol,1.0819403137499982e-13, 1e-17);

}