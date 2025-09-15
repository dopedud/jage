# FetchContent is available in CMake 3.11+
# GenerateExportHeader is available in CMake 3.12+
cmake_minimum_required(VERSION 3.12)

project(game-engine)
set(PROGRAM_NAME engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_VERSION 3.3.10)

set(BUILD_SHARED_LIBS ON CACHE BOOL "build using shared libraries" FORCE)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/_deps")
include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG ${GLFW_VERSION}
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

set(SRC
    engine.cxx
)

set(LIBRARIES
    glfw
)

set(SRC_FILES)
foreach(src ${SRC})
    list(APPEND SRC_FILES "${CMAKE_SOURCE_DIR}/src/${src}")
endforeach()

add_library(${PROGRAM_NAME} SHARED
    ${SRC_FILES}
)
set_target_properties(${PROGRAM_NAME} PROPERTIES 
    OUTPUT_NAME "enginelib"
    PREFIX ""
)

include(GenerateExportHeader)
generate_export_header(${PROGRAM_NAME})

target_link_libraries(${PROGRAM_NAME} PRIVATE ${LIBRARIES})
target_include_directories(${PROGRAM_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_BINARY_DIR}"
)
