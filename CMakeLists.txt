cmake_minimum_required(VERSION 3.6)
project(LightUnitsProj)

# Header-only library
add_library(LightUnits INTERFACE)
target_include_directories(LightUnits INTERFACE "include/")
target_compile_features(LightUnits INTERFACE cxx_std_14)

# Unit tests
add_subdirectory(test)
