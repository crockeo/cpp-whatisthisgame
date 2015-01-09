cmake_minimum_required(VERSION 2.8)
project(whatisthisgame)

# Setting up some project flags.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/lib")

# Setting C++11.
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Setting the set of sources.
set(SOURCES
  src/res/texture.cpp
  src/config.cpp
  src/main.cpp
)

# Setting the executable.
add_executable(whatisthisgame ${SOURCES})

# Looking for OpenGL & GLFW.
find_package(opengl REQUIRED)
find_package(glew REQUIRED)
find_package(glfw REQUIRED)

# Adding the include directories.
include_directories(${OPENGL_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIR}
                    ${GLFW_INCLUDE_DIR})

# Linking the libraries.
target_link_libraries(whatisthisgame ${OPENGL_LIBRARY}
                                     ${GLEW_LIBRARY}
                                     ${GLFW_LIBRARY})
