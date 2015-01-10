#include "game.hpp"

//////////////
// Includes //
#include <thread>

#include "delta.hpp"

//////////
// Code //

// The function to perform updating.
void update(bool* running) {
    Delta delta;
    while (*running) {
    }
}

// The function to perform rendering.
void render(GLFWwindow* window, bool* running) {
    Delta delta;
    while (*running) {
        glfwPollEvents();
        *running = !glfwWindowShouldClose(window);
    }
}

// Starting the update and render threads.
void game::startThreads(GLFWwindow* window, Config cfg) {
    bool running = true;

    std::thread updateThread(update, &running);
    render(window, &running);

    updateThread.join();
}
