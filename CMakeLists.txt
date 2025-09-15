# FetchContent available in CMake 3.11+
# GenerateExportHeader available in CMake 3.12+
# install() command available in CMake 3.15+
cmake_minimum_required(VERSION 3.15)

project(game-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON CACHE BOOL "build using shared libraries" FORCE)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/_deps")
include(FetchContent)

set(GLFW_VERSION 3.3.10)

# Fetch GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG ${GLFW_VERSION}
)

set(GLFW_LIBRARY_TYPE STATIC)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

add_subdirectory("${CMAKE_SOURCE_DIR}/src/glad")
add_subdirectory("${CMAKE_SOURCE_DIR}/src")
