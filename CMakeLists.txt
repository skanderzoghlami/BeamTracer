cmake_minimum_required(VERSION 3.12)  # Consider using 3.12 or higher for better target-based control

project(beamer VERSION 0.1.0 LANGUAGES C CXX)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
file(GLOB IMGUI_SOURCES 
    ${IMGUI_DIR}/*.cpp 
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp 
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC 
    ${IMGUI_DIR} 
    ${IMGUI_DIR}/backends
)
target_link_libraries(ImGui PUBLIC glfw OpenGL::GL)

add_executable(beamer main.cpp)
target_link_libraries(beamer PRIVATE ImGui glfw OpenGL::GL)
target_include_directories(beamer PRIVATE ${CMAKE_SOURCE_DIR}/tutorials)