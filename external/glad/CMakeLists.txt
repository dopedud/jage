add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/gl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(glad PROPERTIES 
    OUTPUT_NAME "glad"
    PREFIX ""
    C_VISIBILITY_PRESET hidden
)

add_library(glad::glad ALIAS glad)