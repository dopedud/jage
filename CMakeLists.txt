cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+

project(game-engine)
set(PROGAM_NAME engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_VERSION 3.3.10)

set(BUILD_SHARED_LIBS ON CACHE BOOL "build shared libraries" FORCE)

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

FetchContent_MakeAvailable(glfw)

set(SRC
    main.cxx
)

set(LIBRARIES
    glfw
)

set(SRC_FILES)
foreach(src ${SRC})
    list(APPEND SRC_FILES "${CMAKE_SOURCE_DIR}/src/${src}")
endforeach()

add_library(SHARED ${PROGAM_NAME}
    ${SRC_FILES}
)

target_link_libraries(${PROGAM_NAME} PRIVATE ${LIBRARIES})
target_include_directories(${PROGAM_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)