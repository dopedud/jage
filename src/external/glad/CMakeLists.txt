set(GLAD_NAME glad CACHE STRING "" FORCE)

add_library(${GLAD_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(${GLAD_NAME} PROPERTIES 
    OUTPUT_NAME "${GLAD_NAME}"
    PREFIX ""
)
