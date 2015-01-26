//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#include "res/texture.hpp"
#include "res/shader.hpp"
#include "assets.hpp"
#include "config.hpp"
#include "delta.hpp"
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

    // Setting up OpenGL, and GLEW>
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    int err = glewInit();
    
    if (err != GLEW_OK) {
        std::cout << "Could not initialize GLEW." << std::endl;
        glfwTerminate();
        return true;
    }

    glClearColor(1.f, 0.f, 1.f, 1.f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Creating the set of assets.
    Assets a;

    // Trying to dynamically fill the assets.
    try {
        AssetLoads als("res/assetspec.txt");
        als.fillAssets(a);
    } catch (std::string& s) { std::cout << s << std::endl; }

    //loadAssets(a);

    // Starting up.
    game::startThreads(window, cfg, a);

    return false;
}

// The entry point to the application.
int main() {
    srand(static_cast<unsigned int>(currentSystemTime()));
    if (startEngine(Config(640, 480, false))) {
        std::cout << "Failed to start the engine." << std::endl;
        return 1;
    }
}
