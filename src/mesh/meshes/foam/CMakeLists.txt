set(FOAM_MESH_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/FoamMesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FoamPolyMesh.cpp
)


target_sources(IncompLib PRIVATE ${FOAM_MESH_FILES})