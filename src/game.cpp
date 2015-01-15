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

        bool my = false, mx = false;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            dy += SPEED * dt;
            my = true;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            dy -= SPEED * dt;
            my = true;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            dx -= SPEED * dt;
            mx = true;
        }
        
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            dx += SPEED * dt;
            mx = true;
        }

        if (!my) {
            if (dy > 0) {
                dy -= SPEED / 10 * dt;
            } else {
                dy += SPEED / 10 * dt;
            }
        }

        if (!mx) {
            if (dx > 0) {
                dx -= SPEED / 10 * dt;
            } else {
                dx += SPEED / 10 * dt;
            }
        }

        gs.position.x += dx * dt;
        gs.position.y += dy * dt;
    }
}

// The function to perform rendering.
void render(GLFWwindow* window, Config cfg, bool& running, const Assets& assets, const GameState& gs, Renders& r) {
    Delta delta;
    while (running) {
        float dt = delta.since();
        if (dt < 1.f / MAX_RENDERS_PER_SECOND)
            delta.sleep((int)((1.f / MAX_RENDERS_PER_SECOND - dt) * 1000.f));

        glClear(GL_COLOR_BUFFER_BIT);

        r["player"]->updateVertices(generateRectangle(gs.position),
                                    rectangleOrder(),
                                    GL_DYNAMIC_DRAW);

        renderAll(window, r);

        glfwSwapBuffers(window);
        glfwPollEvents();
        running = !glfwWindowShouldClose(window);
    }
}

// Starting the update and render threads.
void game::startThreads(GLFWwindow* window, Config cfg, const Assets& assets) {
    bool running = true;
    GameState gs;

    Renders renders;

    renders["player"] = new Render(gs.position,
                                   GL_DYNAMIC_DRAW,
                                   assets.getTexture("res/player/01.png"),
                                   assets.getShader("res/game2d"));

    renders["enemies"] = new Render(generateRectangles(gs.enemies),
                                    rectangleOrders(gs.enemies.size()),
                                    GL_STATIC_DRAW,
                                    assets.getTexture("res/enemy/01.png"),
                                    assets.getShader("res/game2d"));

    renders["background"] = new Render(Rectangle(0, 0, 640, 480),
                                       GL_STATIC_DRAW,
                                       assets.getTexture("res/background.png"),
                                       assets.getShader("res/game2d"));

    std::thread updateThread(update, window, cfg, std::cref(running), std::ref(gs));
    render(window, cfg, std::ref(running), std::cref(assets), std::cref(gs), renders);


    updateThread.join();
}
