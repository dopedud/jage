set(ENGINE_NAME JAGE CACHE STRING "" FORCE)

set(CORE_SRC
    jgpch.cxx
    init.cxx
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

set(RESOURCES_SRC
    resources.cxx
)

set(MATH_SRC
    "math.cxx"
)

set(CORE_SOURCES)
foreach(src ${CORE_SRC})
    list(APPEND CORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()

set(RESOURCES_SOURCES)
foreach(src ${RESOURCES_SRC})
    list(APPEND RESOURCES_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()

set(MATH_SOURCES)
foreach(src ${MATH_SRC})
    list(APPEND MATH_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${src})
endforeach()

add_library(${ENGINE_NAME} SHARED ${CORE_SOURCES})
add_library(${ENGINE_NAME}_RESOURCES SHARED ${RESOURCES_SOURCES})
add_library(${ENGINE_NAME}_MATH SHARED ${MATH_SOURCES})

# for now it should be safe to remove ${ENGINE_NAME}_ENABLE_ASSERTS but just leave it for now for every module
target_compile_definitions(${ENGINE_NAME} PRIVATE
    ${ENGINE_NAME}_EXPORT
    ${ENGINE_NAME}_ENABLE_ASSERTS
)

target_compile_definitions(${ENGINE_NAME}_RESOURCES PRIVATE
    ${ENGINE_NAME}_RESOURCES_EXPORT
    ${ENGINE_NAME}_ENABLE_ASSERTS
)

target_compile_definitions(${ENGINE_NAME}_MATH PRIVATE
    ${ENGINE_NAME}_MATH_EXPORT
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

set_target_properties(${ENGINE_NAME}_RESOURCES PROPERTIES 
    OUTPUT_NAME ${ENGINE_NAME}.Resources
    PREFIX ""

    ${VISIBILITY_PRESETS}
)

set_target_properties(${ENGINE_NAME}_MATH PROPERTIES 
    OUTPUT_NAME ${ENGINE_NAME}.Math
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
)

target_precompile_headers(${ENGINE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/jgpch.h)

target_link_libraries(${ENGINE_NAME} PUBLIC ${PUBLIC_LIBRARIES})
target_link_libraries(${ENGINE_NAME} PRIVATE ${PRIVATE_LIBRARIES})
target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${ENGINE_NAME}_RESOURCES PRIVATE tinygltf stb_image)
target_link_libraries(${ENGINE_NAME}_RESOURCES PUBLIC ${ENGINE_NAME})
target_include_directories(${ENGINE_NAME}_RESOURCES PUBLIC ${CMAKE_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${ENGINE_NAME}_MATH PRIVATE glm)
target_link_libraries(${ENGINE_NAME}_MATH PUBLIC ${ENGINE_NAME})
target_include_directories(${ENGINE_NAME}_MATH PUBLIC ${CMAKE_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${ENGINE_NAME} PRIVATE ${ENGINE_NAME}_RESOURCES ${ENGINE_NAME}_MATH)