# FetchContent available in CMake 3.11+
# GenerateExportHeader available in CMake 3.12+
# install() command available in CMake 3.15+
cmake_minimum_required(VERSION 3.15)

project(game-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/_deps)

include(FetchContent)
include(CustomTargets)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)

set(CMAKE_INSTALL_MESSAGE LAZY)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/installs)

# FETCH SPDLOG
set(SPDLOG_VERSION v1.15.0)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG ${SPDLOG_VERSION}
)

set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(spdlog)
# END FETCH SPDLOG

# FETCH GLFW
set(GLFW_VERSION 3.3.10)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG ${GLFW_VERSION}
)

set(GLFW_LIBRARY_TYPE "STATIC" CACHE STRING "" FORCE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)
# END FETCH GLFW

# BUILD GLAD
# NOTE: GLAD is a special case for dependency management because unlike other dependencies where you have to fetch them
# online from GitHub or other repositories, GLAD does not have that and instead let developers fetch them via a
# download from a web service. Thus, it might seem like GLAD is part of the project, but really it's a dependency
# handled manually and should be treated like one (that means no modifying willy-nilly!!!).
add_subdirectory(${CMAKE_SOURCE_DIR}/src/glad)
# END BUILD GLAD

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_SOURCE_DIR}/sandbox)

install(TARGETS ${EXECUTABLE_NAME} ${ENGINE_NAME} ${LIBRARIES}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)

