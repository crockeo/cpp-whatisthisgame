//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "res/texture.hpp"
#include "res/shader.hpp"
#include "assets.hpp"
#include "config.hpp"
#include "game.hpp"

//////////
// Code //

// Starting the engine.
bool startEngine(Config cfg) {
    // Starting up GLFW.
    if (!glfwInit()) {
        std::cout << "Could not start GLFW." << std::endl;
        return true;
    }

    // Grabbing the monitor if you need to.
    GLFWmonitor* monitor = cfg.fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    if (cfg.fullscreen && monitor == nullptr) {
        std::cout << "Could not get the primary monitor." << std::endl;
        glfwTerminate();
        return true;
    }

    // Creating the window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        cfg.windowWidth,
        cfg.windowHeight,
        "whatisthisgame",
        monitor,
        nullptr
    );

    if (window == nullptr) {
        std::cout << "Could not create the window." << std::endl;
        glfwTerminate();
        return true;
    }

    // Getting everything ready and kicking off the render & update threads.
    glfwMakeContextCurrent(window);
    int err = glewInit();
    
    if (err != GLEW_OK) {
        std::cout << "Could not initialize GLEW." << std::endl;
        glfwTerminate();
        return true;
    }

    Assets a;
    loadAssets(a);

    game::startThreads(window, cfg);

    return false;
}

// The entry point to the application.
int main() {
    if (startEngine(Config(640, 480, false))) {
        std::cout << "Failed to start the engine." << std::endl;
        return 1;
    }
}
