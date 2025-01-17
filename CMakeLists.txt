cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(PROJECT_NAME OpenGL-Setup)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
src/main.cpp
src/Renderer/ShaderProgram.cpp 
src/Renderer/ShaderProgram.h
src/Renderer/Camera.h
src/ImageRenderer/stb_image.h
src/ImageRenderer/stb_image.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)
