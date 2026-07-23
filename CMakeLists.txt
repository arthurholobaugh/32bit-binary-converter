cmake_minimum_required(VERSION 3.16)
project(binary_converter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.15.2
)
FetchContent_MakeAvailable(Catch2)

add_library(converter converter.cpp)
target_include_directories(converter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(binary_converter main.cpp)
target_link_libraries(binary_converter PRIVATE converter)

enable_testing()
add_executable(converter_tests tests/test_converter.cpp)
target_link_libraries(converter_tests PRIVATE converter Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(converter_tests)
