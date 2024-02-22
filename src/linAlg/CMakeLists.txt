set(LINALGOPS_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/LinAlgOps.cpp
)


target_sources(IncompLib PRIVATE ${LINALGOPS_FILES})