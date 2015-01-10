#ifndef _GAME_HPP_
#define _GAME_HPP_

//////////////
// Includes //
#include <GLFW/glfw3.h>
#include "config.hpp"

//////////
// Code //

namespace game {
    // Starting the update and render threads.
    void startThreads(GLFWwindow*, Config);
}

#endif
