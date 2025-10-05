set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/_deps)

include(FetchContent)

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

# FETCH ARGPARSE
set(ARGPARSE_VERSION v3.2)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG ${ARGPARSE_VERSION}
)

set(ARGPARSE_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ARGPARSE_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(argparse)

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

# FETCH DEAR IMGUI
set(DEAR_IMGUI_VERSION v1.92.3-docking)
FetchContent_Declare(
    dear_imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG ${DEAR_IMGUI_VERSION}
)

FetchContent_MakeAvailable(dear_imgui)
# END FETCH DEAR IMGUI

# BUILD GLAD
# NOTE: GLAD is a special case for dependency management because unlike other dependencies where you have to fetch them
# online from GitHub or other repositories, GLAD does not have that and instead let developers fetch them via a
# download from a web service. Thus, it might seem like GLAD is part of the project, but really it's a dependency
# handled manually and should be treated like one (that means no modifying willy-nilly!!!).
add_subdirectory(${CMAKE_SOURCE_DIR}/src/external/glad)
# END BUILD GLAD

# BUILD DEAR IMGUI
set(DEAR_IMGUI_NAME "dear_imgui" CACHE STRING "" FORCE)

add_library(dear_imgui STATIC
    ${dear_imgui_SOURCE_DIR}/imgui.cpp
    ${dear_imgui_SOURCE_DIR}/imgui_draw.cpp
    ${dear_imgui_SOURCE_DIR}/imgui_tables.cpp
    ${dear_imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${dear_imgui_SOURCE_DIR}/imgui_demo.cpp

    ${dear_imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${dear_imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(dear_imgui PUBLIC
    ${dear_imgui_SOURCE_DIR}
    ${dear_imgui_SOURCE_DIR}/backends
)

target_link_libraries(dear_imgui PUBLIC glfw glad)

set_target_properties(${GLAD_NAME} PROPERTIES 
    OUTPUT_NAME "${GLAD_NAME}"
    PREFIX ""
)
# END BUILD DEAR IMGUI
