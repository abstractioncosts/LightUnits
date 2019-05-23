cmake_minimum_required(VERSION 3.6)
project(LightUnitsProj)

# Header-only library
add_library(LightUnits INTERFACE)
target_include_directories(LightUnits INTERFACE "include/")
target_compile_features(LightUnits INTERFACE cxx_std_14)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # using regular Clang or AppleClang
  target_compile_options(LightUnits INTERFACE "-Wno-mismatched-tags")
endif()

# Unit tests
add_subdirectory(test)
