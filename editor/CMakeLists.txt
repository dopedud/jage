set(EDITOR_NAME editor CACHE STRING "" FORCE)

add_executable(${EDITOR_NAME} editor.cxx)

target_link_libraries(${EDITOR_NAME} PRIVATE ${ENGINE_NAME})
