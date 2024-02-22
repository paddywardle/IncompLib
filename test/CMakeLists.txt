include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)

target_link_libraries(GTest::GTest INTERFACE gtest_main)

file(GLOB_RECURSE TESTS "*.cpp")

add_executable(incomp_lib_tests ${TESTS})

target_link_libraries(incomp_lib_tests
  PRIVATE
  GTest::GTest
  IncompLib
)