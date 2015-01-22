#include "game.hpp"

//////////////
// Includes //
#include <thread>

#include "entities/player.hpp"
#include "gamestate.hpp"
#include "rendering.hpp"
#include "delta.hpp"

//////////
// Code //

// Defining the maximums for updates and rendering.
#define MAX_UPDATES_PER_SECOND 300
#define MAX_RENDERS_PER_SECOND 120

// The speed of the player.
#define SPEED 500

// The current speed of the player.
float dx = 0, dy = 0;

// The function to perform updating.
void update(GLFWwindow* window, Config cfg, const bool& running, GameState& gs) {
    Delta delta;
    while (running) {
        float dt = delta.since();
        if (dt < 1.f / MAX_UPDATES_PER_SECOND)
            delta.sleep((int)((1.f / MAX_UPDATES_PER_SECOND - dt) * 1000.f));

        gs.updateAll(window, gs, dt);
    }
}

// The function to perform rendering.
void render(GLFWwindow* window, Config cfg, bool& running, const Assets& assets, const GameState& gs, Renders& renders) {
    Delta delta;
    while (running) {
        float dt = delta.since();
        if (dt < 1.f / MAX_RENDERS_PER_SECOND)
            delta.sleep((int)((1.f / MAX_RENDERS_PER_SECOND - dt) * 1000.f));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        gs.renderAll(window, renders);
        renders.renderAll(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
        running = !glfwWindowShouldClose(window);
    }
}

// Starting the update and render threads.
void game::startThreads(GLFWwindow* window, Config cfg, const Assets& assets) {
    bool running = true;
    Renders renders(5);

    GameState gs;
    initializeGameState(window, gs, assets.getAnimationTimers());
    gs.initRenderAll(window, assets, renders);

    std::thread updateThread(update, window, cfg, std::cref(running), std::ref(gs));
    render(window, cfg, std::ref(running), std::cref(assets), std::cref(gs), renders);


    updateThread.join();
}
