set(ENGINE_NAME JAGE CACHE STRING "" FORCE)

set(CORE_SRC
    jgpch.cxx
    init.cxx
    resources.cxx
    "log.cxx"
    event.cxx
    "input.cxx"
    window.cxx
    renderer.cxx

    platform/glfw/input.cxx
    platform/glfw/opengl3/window.cxx
    platform/glfw/opengl3/renderer.cxx
    platform/glfw/opengl3/game_layer.cxx
    platform/glfw/opengl3/imgui_layer.cxx
)

set(CORE_SOURCES)
foreach(src ${CORE_SRC})
    list(APPEND CORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()

add_library(${ENGINE_NAME} SHARED ${CORE_SOURCES})

target_compile_definitions(${ENGINE_NAME} PRIVATE
    ENGINE_INNAME=${ENGINE_NAME}
    ${ENGINE_NAME}_EXPORT
    ${ENGINE_NAME}_ENABLE_ASSERTS
)

set_target_properties(${ENGINE_NAME} PROPERTIES 
    OUTPUT_NAME ${ENGINE_NAME}
    PREFIX ""

    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
)

set(PUBLIC_LIBRARIES
    spdlog::spdlog
)

set(PRIVATE_LIBRARIES
    glfw
    glad
    glm
    dear_imgui
    tinygltf
    stb_image
)

target_link_libraries(${ENGINE_NAME} PUBLIC ${PUBLIC_LIBRARIES})
target_link_libraries(${ENGINE_NAME} PRIVATE ${PRIVATE_LIBRARIES})
target_precompile_headers(${ENGINE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/jgpch.h)
target_include_directories(${ENGINE_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
