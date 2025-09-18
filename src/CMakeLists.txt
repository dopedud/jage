set(ENGINE_NAME JAGE CACHE STRING "" FORCE)

set(SRC
    logger.cxx
)

set(SRC_FILES)
foreach(src ${SRC})
    list(APPEND SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${src}")
endforeach()

add_library(${ENGINE_NAME} SHARED ${SRC_FILES})

set_target_properties(${ENGINE_NAME} PROPERTIES 
    OUTPUT_NAME ${ENGINE_NAME}
    PREFIX ""
)

include(GenerateExportHeader)
generate_export_header(${ENGINE_NAME}
    EXPORT_MACRO_NAME ${ENGINE_NAME}_API
    EXPORT_FILE_NAME ${CMAKE_SOURCE_DIR}/include/${ENGINE_NAME}_export.h
)

set(LIBRARIES
    spdlog::spdlog
    glfw
    glad
)

target_link_libraries(${ENGINE_NAME} PRIVATE ${LIBRARIES})
target_include_directories(${ENGINE_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
