#include "game.hpp"

//////////////
// Includes //
#include <thread>

#include "gamestate.hpp"
#include "rendering.hpp"
#include "delta.hpp"

//////////
// Code //

// Defining the maximums for updates and rendering.
#define MAX_UPDATES_PER_SECOND 300
#define MAX_RENDERS_PER_SECOND 120

// The speed of the player.
#define SPEED 300

// The function to perform updating.
void update(GLFWwindow* window, Config cfg, const bool& running, GameState& gs) {
    Delta delta;
    while (running) {
        float dt = delta.since();
        if (dt < 1.f / MAX_UPDATES_PER_SECOND)
            delta.sleep((int)((1.f / MAX_UPDATES_PER_SECOND - dt) * 1000.f));

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            gs.y += SPEED * dt;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            gs.y -= SPEED * dt;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            gs.x -= SPEED * dt;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            gs.x += SPEED * dt;
    }
}

// The function to perform rendering.
void render(GLFWwindow* window, Config cfg, bool& running, const Assets& assets, const GameState& gs) {
    Delta delta;
    while (running) {
        float dt = delta.since();
        if (dt < 1.f / MAX_RENDERS_PER_SECOND)
            delta.sleep((int)((1.f / MAX_RENDERS_PER_SECOND - dt) * 1000.f));

        glClear(GL_COLOR_BUFFER_BIT);
        rendering::renderRectangle(0, 0, 640, 480, assets.getTexture("res/background.png"), assets.getShader("res/game2d"));
        rendering::renderRectangle(gs.x, gs.y, gs.w, gs.h, assets.getTexture("res/player/01.png"), assets.getShader("res/game2d"));

        glfwSwapBuffers(window);
        glfwPollEvents();
        running = !glfwWindowShouldClose(window);
    }
}

// Starting the update and render threads.
void game::startThreads(GLFWwindow* window, Config cfg, const Assets& assets) {
    bool running = true;
    GameState gs(0, 0, 50, 50);

    std::thread updateThread(update, window, cfg, std::cref(running), std::ref(gs));
    render(window, cfg, std::ref(running), std::cref(assets), std::cref(gs));

    updateThread.join();
}
