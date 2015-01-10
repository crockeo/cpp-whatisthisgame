#ifndef _GAME_HPP_
#define _GAME_HPP_

//////////////
// Includes //
#include <GLFW/glfw3.h>
#include "config.hpp"

//////////
// Code //

namespace game {
    // Spawning a separate thread to update the game.
    void spawnUpdateThread(GLFWwindow*, Config);

    // Spawning the synchronous thread to render the game.
    void spawnRenderThread(GLFWwindow*, Config);
}

#endif
