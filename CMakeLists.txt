# ------------------------------------------------------------------------------
# Main CMake build file. All other CMakeLists.txt and .cmake files are included
# here to be executed altogether.
#
# Table of Contents:
# - GLOBAL SETTINGS
# - OPTIONS
# - HELPER CODE
# - TARGETS
# - INSTALLS
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.21)

project(jage
    VERSION         0.1.0
    DESCRIPTION     "JAGE - a 3D game engine from scratch."
    LANGUAGES       C CXX
)

# ------------------------------------------------------------------------------
# GLOBAL SETTINGS
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Hidden by default: the engine is a shared library and everything crossing the
# DLL boundary must be tagged explicitly with JAGE_API (see engine/CMakeLists.txt).
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/lib")

set(CMAKE_INSTALL_MESSAGE LAZY)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/installs")

# ------------------------------------------------------------------------------
# OPTIONS
# ------------------------------------------------------------------------------
option(JAGE_BUILD_SANDBOX       "build the Sandbox test application" ON)
option(JAGE_WARNINGS_AS_ERRORS  "treat compiler warnings as errors" OFF)

# ------------------------------------------------------------------------------
# HELPER CODE
# ------------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CustomTargets)
include(CompilerWarnings)
include(Dependencies)

# ------------------------------------------------------------------------------
# TARGETS
# ------------------------------------------------------------------------------
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/engine)
# add_subdirectory(${CMAKE_SOURCE_DIR}/editor)

if(JAGE_BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()

message(STATUS "")
message(STATUS "JAGE v${PROJECT_VERSION}")
message(STATUS "    build type ....... ${CMAKE_BUILD_TYPE}")
message(STATUS "    compiler ......... ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "    generator ........ ${CMAKE_GENERATOR}")
message(STATUS "    output ........... ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "")

# ------------------------------------------------------------------------------
# INSTALLS
# ------------------------------------------------------------------------------
install(TARGETS
    ${GAME_NAME}
    ${ENGINE_NAME}

    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY assets/ DESTINATION assets)
