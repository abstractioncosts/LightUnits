cmake_minimum_required(VERSION 3.6)
project(LightUnitsProj)

# Header-only library
add_library(LightUnits INTERFACE)
target_include_directories(LightUnits INTERFACE "include/")
target_compile_features(LightUnits INTERFACE cxx_std_14)

# Unit tests
set(SOURCE_FILES test/CatchMain.cpp test/BaseUnitTest.cpp test/ExampleConversionTest.cpp test/ValueSystemTest.cpp)
add_executable(LightUnitsTest ${SOURCE_FILES})
target_link_libraries(LightUnitsTest LightUnits)
target_include_directories(LightUnitsTest PRIVATE "example/")
target_include_directories(LightUnitsTest PRIVATE "external/Catch/include")
