set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/_deps)
include(FetchContent)

# build static 3rd-party libraries, links to engine directly
set(BUILD_SHARED_LIBS OFF CACHE BOOL "build shared libraries by default" FORCE)

# LIST OF DEPENDENCIES:
#
# SPDLOG
# GLFW
# GLM
# GLAD
# DEAR IMGUI
# STB_IMAGE
# TINYGLTF
# FLECS

# FETCH SPDLOG
set(SPDLOG_VERSION v1.15.0)
FetchContent_Declare(
    spdlog_repo
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG ${SPDLOG_VERSION}
)

FetchContent_MakeAvailable(spdlog_repo)
# END FETCH SPDLOG

# FETCH GLFW
set(GLFW_VERSION 3.3.10)
FetchContent_Declare(
    glfw_repo
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG ${GLFW_VERSION}
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw_repo)
# END FETCH GLFW

# FETCH GLM
set(GLM_VERSION 1.0.2)
FetchContent_Declare(
    glm_repo
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG ${GLM_VERSION}
)

set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glm_repo)
# END FETCH GLM

# FETCH DEAR IMGUI
set(DEAR_IMGUI_VERSION v1.92.3-docking)
FetchContent_Declare(
    dear_imgui_repo
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG ${DEAR_IMGUI_VERSION}
)

FetchContent_MakeAvailable(dear_imgui_repo)
# END FETCH DEAR IMGUI

# FETCH STB_IMAGE
set(STB_IMAGE_VERSION f1c79c02822848a9bed4315b12c8c8f3761e1296)
FetchContent_Declare(
    stb_image_repo
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG ${STB_IMAGE_VERSION}
)

FetchContent_MakeAvailable(stb_image_repo)
# END FETCH STB_IMAGE

# FETCH TINYGLTF
set(TINYGLTF_VERSION v2.9.6)
FetchContent_Declare(
    tinygltf_repo
    GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
    GIT_TAG ${TINYGLTF_VERSION}
)

set(TINYGLTF_HEADER_ONLY ON CACHE BOOL "On: header-only mode. Off: create tinygltf library(No TINYGLTF_IMPLEMENTATION required in your project)" FORCE)
set(TINYGLTF_BUILD_LOADER_EXAMPLE OFF CACHE BOOL "Build loader_example(load glTF and dump infos)" FORCE)
set(TINYGLTF_INSTALL OFF CACHE BOOL "Install tinygltf files during install step. Usually set to OFF if you include tinygltf through add_subdirectory()" FORCE)
set(TINYGLTF_INSTALL_VENDOR OFF CACHE BOOL "Install vendored nlohmann/json and nothings/stb headers" FORCE)

FetchContent_MakeAvailable(tinygltf_repo)
# END FETCH TINYGLTF

# FETCH ASSIMP
set(ASSIMP_VERSION v6.0.2)
FetchContent_Declare(
    assimp_repo
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG ${ASSIMP_VERSION}
)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "If the test suite for Assimp is built in addition to the library." FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "Install Assimp library. Disable this if you want to use Assimp as a submodule." FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "Install MSVC debug files." FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "Inject debug postfix in .a/.so/.lib/.dll lib names" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Treat all warnings as errors." FORCE)

FetchContent_MakeAvailable(assimp_repo)
# END FETCH ASSIMP

# FETCH FLECS
set(FLECS_VERSION v4.1.2)
FetchContent_Declare(
    flecs_repo
    GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
    GIT_TAG ${FLECS_VERSION}
)

# NOTE: Flecs has their own CMakeLists.txt that is intrusive to this project (like installing its own header files),
# thus a custom build procedure is written to work around this issue.

FetchContent_GetProperties(flecs_repo)
if(NOT flecs_repo_POPULATED)
    FetchContent_Populate(flecs_repo)
endif()

file(GLOB_RECURSE FLECS_SOURCES "${flecs_repo_SOURCE_DIR}/src/*.c")
add_library(flecs STATIC ${FLECS_SOURCES})
target_include_directories(flecs PUBLIC ${flecs_repo_SOURCE_DIR}/include PRIVATE ${flecs_repo_SOURCE_DIR}/src)

if(WIN32)
    target_link_libraries(flecs wsock32 ws2_32 dbghelp)
endif()

if (UNIX)
    target_link_libraries(flecs pthread)
endif()

target_compile_definitions(flecs PRIVATE
    FLECS_CUSTOM_BUILD
    FLECS_LOG
    FLECS_DOC
    FLECS_CPP
    FLECS_META
    FLECS_SYSTEM
    FLECS_PIPELINE
    FLECS_QUERY_DSL
)
# END FETCH FLECS

# BUILD GLAD
# NOTE: GLAD is a special case for dependency management because unlike other dependencies where you have to fetch them
# online from GitHub or other repositories, GLAD does not have that and instead let developers fetch them via a
# download from a web service. Thus, it might seem like GLAD is part of the project, but really it's a dependency
# handled manually and should be treated like one (that means no modifying willy-nilly!!!).
add_subdirectory(${CMAKE_SOURCE_DIR}/src/external/glad)
# END BUILD GLAD

# BUILD DEAR IMGUI
# NOTE: Dear ImGui is build-agnostic. That is, it lets users build its files using their own build system. Hence, only
# the required files are used to build Dear ImGui.
add_library(dear_imgui STATIC
    ${dear_imgui_repo_SOURCE_DIR}/imgui.cpp
    ${dear_imgui_repo_SOURCE_DIR}/imgui_draw.cpp
    ${dear_imgui_repo_SOURCE_DIR}/imgui_tables.cpp
    ${dear_imgui_repo_SOURCE_DIR}/imgui_widgets.cpp
    ${dear_imgui_repo_SOURCE_DIR}/imgui_demo.cpp

    ${dear_imgui_repo_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${dear_imgui_repo_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(dear_imgui PUBLIC
    ${dear_imgui_repo_SOURCE_DIR}
    ${dear_imgui_repo_SOURCE_DIR}/backends
)

target_link_libraries(dear_imgui PUBLIC glfw glad)
# END BUILD DEAR IMGUI

# BUILD STB_IMAGE
add_library(stb_image INTERFACE)

target_include_directories(stb_image INTERFACE ${stb_image_repo_SOURCE_DIR})
# END BUILD STB_IMAGE