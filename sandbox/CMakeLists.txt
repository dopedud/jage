set(EXECUTABLE_NAME game CACHE STRING "" FORCE)

add_executable(${EXECUTABLE_NAME} main.cxx)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${ENGINE_NAME})