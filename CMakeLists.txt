cmake_minimum_required(VERSION 3.0.0)
project(MoChengEngine VERSION 0.1.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
 
include_directories(${PROJECT_SOURCE_DIR}/lib/Include  ${PROJECT_SOURCE_DIR}/lib  ${PROJECT_SOURCE_DIR})

FIND_LIBRARY(VULKAN vulkan ${PROJECT_SOURCE_DIR}/lib)
FIND_LIBRARY(GLFW libglfw3 ${PROJECT_SOURCE_DIR}/lib/glfw3)

add_subdirectory(FrameWork)
add_executable(MoChengEngine main.cpp)
target_link_libraries(MoChengEngine ${VULKAN} ${GLFW} framework)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
 
