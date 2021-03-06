cmake_minimum_required(VERSION 2.8)
project(whatisthisgame)

# Finding cmake files.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Setting up some project flags.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/lib")

# Setting C++11.
set(CMAKE_CXX_FLAGS "-O2 -std=c++11 ${CMAKE_CXX_FLAGS}")

# Setting the set of sources.
set(SOURCES
  src/entities/explodecontroller.cpp
  src/entities/bulletcontroller.cpp
  src/entities/enemycontroller.cpp
  src/entities/scoretracker.cpp
  src/entities/lifetracker.cpp
  src/entities/background.cpp
  src/entities/controller.cpp
  src/entities/fpscounter.cpp
  src/entities/bullet.cpp
  src/entities/player.cpp
  src/res/spritesheet.cpp
  src/res/ssanimation.cpp
  src/entities/enemy.cpp
  src/res/animation.cpp
  src/res/texture.cpp
  src/res/shader.cpp
  src/gamestate.cpp
  src/rectangle.cpp
  src/rendering.cpp
  src/observer.cpp
  src/res/font.cpp
  src/assets.cpp
  src/config.cpp
  src/events.cpp
  src/delta.cpp
  src/timer.cpp
  src/utils.cpp
  src/game.cpp
  src/main.cpp
)

# Setting the executable.
add_executable(whatisthisgame ${SOURCES})

# Looking for OpenGL & GLFW.
find_package(freetype REQUIRED)
find_package(opengl REQUIRED)
find_package(bzip2 REQUIRED)
find_package(glew REQUIRED)
find_package(glfw REQUIRED)
find_package(zlib REQUIRED)
find_package(png REQUIRED)

# Adding the include directories.
include_directories(${FREETYPE_INCLUDE_DIRS}
                    ${OPENGL_INCLUDE_DIR}
                    ${BZIP2_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIR}
                    ${GLFW_INCLUDE_DIR}
                    ${ZLIB_INCLUDE_DIR}
                    ${PNG_INCLUDE_DIR})

# Linking the libraries.
target_link_libraries(whatisthisgame ${FREETYPE_LIBRARIES}
                                     ${OPENGL_LIBRARY}
                                     ${BZIP2_LIBRARY}
                                     ${GLEW_LIBRARY}
                                     ${GLFW_LIBRARY}
                                     ${ZLIB_LIBRARY}
                                     ${PNG_LIBRARY})
