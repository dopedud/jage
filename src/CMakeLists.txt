set(ENGINE_NAME engine CACHE STRING "" FORCE)

set(SRC
    engine.cxx
)

set(SRC_FILES)
foreach(src ${SRC})
    list(APPEND SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${src}")
endforeach()

add_library(${ENGINE_NAME} SHARED
    ${SRC_FILES}
)

set_target_properties(${ENGINE_NAME} PROPERTIES 
    OUTPUT_NAME "${ENGINE_NAME}"
    PREFIX ""
)

include(GenerateExportHeader)
generate_export_header(${ENGINE_NAME})

set(LIBRARIES
    glfw
    glad
)

target_link_libraries(${ENGINE_NAME} PRIVATE ${LIBRARIES})
target_include_directories(${ENGINE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
