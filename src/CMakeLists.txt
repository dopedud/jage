set(ENGINE_NAME JAGE CACHE STRING "" FORCE)

# TODO: debloat this heap of source files; have them separated into logical modules that have one-way dependencies
set(CORE_SRC
    jgpch.cxx
    init.cxx
    "log.cxx"
    event.cxx
    "input.cxx"
    window.cxx
    renderer.cxx
    resources.cxx
    "math.cxx"

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

# for now it should be safe to remove ${ENGINE_NAME}_ENABLE_ASSERTS but just leave it for now
target_compile_definitions(${ENGINE_NAME} PRIVATE
    ${ENGINE_NAME}_EXPORT
    ${ENGINE_NAME}_ENABLE_ASSERTS
)

set(VISIBILITY_PRESETS
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
)

set_target_properties(${ENGINE_NAME} PROPERTIES 
    OUTPUT_NAME ${ENGINE_NAME}
    PREFIX ""

    ${VISIBILITY_PRESETS}
)

set(PUBLIC_LIBRARIES
    spdlog::spdlog
)

set(PRIVATE_LIBRARIES
    glfw
    glad
    dear_imgui
    tinygltf
    stb_image
    glm
)

target_precompile_headers(${ENGINE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/jgpch.h)

target_link_libraries(${ENGINE_NAME} PUBLIC ${PUBLIC_LIBRARIES})
target_link_libraries(${ENGINE_NAME} PRIVATE ${PRIVATE_LIBRARIES})
target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})