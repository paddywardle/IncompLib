add_library(IncompLib)

add_subdirectory(mesh)

add_subdirectory(linAlg)

add_subdirectory(fields)

find_package(OpenMP REQUIRED)

target_link_libraries(IncompLib PUBLIC OpenMP::OpenMP_CXX)