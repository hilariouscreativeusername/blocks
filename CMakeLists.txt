cmake_minimum_required(VERSION 3.21)
project(Blocks)

# Source files
set(SOURCE_FILES src/main.cpp)
source_group("src" FILES ${SOURCE_FILES})

set(WINDOW_FILES src/window/window.h src/window/window.cpp src/window/window_utils.h src/window/window_utils.cpp)
source_group("src/window" FILES ${WINDOW_FILES})

set(GRAPHICS_FILES src/graphics/vertex_array.h src/graphics/vertex_array.cpp src/graphics/shader.h src/graphics/shader.cpp)
source_group("src/graphics" FILES ${GRAPHICS_FILES})

set(SHADER_FILES src/shaders/chunk_shader.vert.glsl src/shaders/chunk_shader.frag.glsl)
source_group("src/shaders" FILES ${SHADER_FILES})

set(ENTITY_FILES src/entities/entity.h)
source_group("src/entities" FILES ${ENTITY_FILES})

# Executable options
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${WINDOW_FILES} ${GRAPHICS_FILES} ${SHADER_FILES} ${ENTITY_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Dependencies
add_subdirectory(depend/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(depend/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

target_include_directories(${PROJECT_NAME} PRIVATE depend/glm)

# Platform-specific stuff
if(WIN32)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
  set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
