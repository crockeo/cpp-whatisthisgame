//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "res/texture.hpp"
#include "res/shader.hpp"

#include "config.hpp"

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

    // Spawning the update & render threads.
    glfwMakeContextCurrent(window);
    int err = glewInit();
    
    if (err != GLEW_OK) {
        std::cout << "Could not initialize GLEW." << std::endl;
        glfwTerminate();
        return true;
    }

    Texture t("res/bullet.png");
    Texture t2("res/what.png");
    Shader s("res/game2d");

    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glColor3f(1.f, 0.3f, 0.6f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.5f,  0.5f);
            glVertex2f(-0.5f,  0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return false;
}

// The entry point to the application.
int main() {
    if (startEngine(Config(640, 480, false))) {
        std::cout << "Failed to start the engine." << std::endl;
        return 1;
    }
}
