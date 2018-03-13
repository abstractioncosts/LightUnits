include(ExternalProject)
find_package(Git)

list(APPEND CATCH_CMAKE_ARGS
        "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external"
        "-DNO_SELFTEST=true"
        )

if(GIT_FOUND)
    # add catch
    ExternalProject_Add(
            catch
            PREFIX ${CMAKE_BINARY_DIR}/catch
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.0.1
            CMAKE_ARGS ${CATCH_CMAKE_ARGS}
            LOG_DOWNLOAD 1
            UPDATE_DISCONNECTED 1
    )
else()
    # assume catch is installed in a system directory
    add_custom_target(catch)
endif()

set(SOURCE_FILES CatchMain.cpp BaseUnitTest.cpp ExampleConversionTest.cpp ValueSystemTest.cpp)
add_executable(LightUnitsTest ${SOURCE_FILES})
target_link_libraries(LightUnitsTest LightUnits)
add_dependencies(LightUnitsTest catch)
target_include_directories(LightUnitsTest PRIVATE "example/")
target_include_directories(LightUnitsTest PRIVATE ${CMAKE_BINARY_DIR}/external/include/catch)
