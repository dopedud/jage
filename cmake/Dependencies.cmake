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
