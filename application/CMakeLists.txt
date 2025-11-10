set(GAME_NAME game CACHE STRING "" FORCE)

add_executable(${GAME_NAME} main.cxx)

target_link_libraries(${GAME_NAME} PRIVATE ${ENGINE_NAME})
