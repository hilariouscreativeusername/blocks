cmake_minimum_required(VERSION 3.21)
project(Blocks)

# Source files
set(SOURCE_FILES src/main.cpp)
source_group("src" FILES ${SOURCE_FILES})

set(WINDOW_FILES src/window/window.h src/window/window.cpp src/window/window_utils.h src/window/window_utils.cpp)
source_group("src/window" FILES ${WINDOW_FILES})

set(GRAPHICS_FILES src/graphics/vertex_array.h src/graphics/vertex_array.cpp src/graphics/shader.h src/graphics/shader.cpp src/graphics/texture.h src/graphics/texture.cpp src/graphics/texture_array.h src/graphics/texture_array.cpp)
source_group("src/graphics" FILES ${GRAPHICS_FILES})

set(SHADER_FILES src/shaders/chunk_shader.vert.glsl src/shaders/chunk_shader.frag.glsl)
source_group("src/shaders" FILES ${SHADER_FILES})

set(ENTITY_FILES src/entities/entity.h src/entities/camera.h src/entities/camera.cpp)
source_group("src/entities" FILES ${ENTITY_FILES})

set(WORLD_FILES src/world/chunk.h src/world/chunk.cpp src/world/block.h src/world/block.cpp src/world/chunk_mesh_generator.h src/world/chunk_mesh_generator.cpp)
source_group("src/world" FILES ${WORLD_FILES})

# Executable options
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${WINDOW_FILES} ${GRAPHICS_FILES} ${SHADER_FILES} ${ENTITY_FILES} ${WORLD_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Dependencies
add_subdirectory(depend/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(depend/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

target_include_directories(${PROJECT_NAME} PRIVATE depend/glm)

target_include_directories(${PROJECT_NAME} PRIVATE depend/stb)

add_subdirectory(depend/cartilage)
target_link_libraries(${PROJECT_NAME} PRIVATE cartilage)

# Platform-specific stuff
if(WIN32)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
  set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES XCODE_GENERATE_SCHEME TRUE XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

