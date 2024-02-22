set(FOAM_MESH_LOADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/FoamPolyMeshLoader.cpp
)

target_sources(IncompLib PRIVATE ${FOAM_MESH_LOADER_FILES})