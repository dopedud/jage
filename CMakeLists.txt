# FetchContent available in CMake 3.11+
# GenerateExportHeader available in CMake 3.12+
# install() command available in CMake 3.15+
# target_precompile_headers() available in CMake 3.16+
cmake_minimum_required(VERSION 3.16)

project(game-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include helper code from cmake directory
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)

set(CMAKE_INSTALL_MESSAGE LAZY)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/installs)

include(Dependencies)
include(CustomTargets)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

# add_subdirectory(${CMAKE_SOURCE_DIR}/editor)

add_subdirectory(${CMAKE_SOURCE_DIR}/application)

install(TARGETS
    ${GAME_NAME}
    ${ENGINE_NAME}
    ${ENGINE_NAME}_RESOURCES
    ${ENGINE_NAME}_MATH

    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY resources/ DESTINATION resources)
