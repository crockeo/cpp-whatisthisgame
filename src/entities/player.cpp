#include "player.hpp"

//////////
// Code //

#define SPEED 500
#define MIN_SPEED 1

// Creating a new player at a given location.
Player::Player(float x, float y) :
        Entity(Rectangle(x, y, Player::width, Player::height)) {
    this->dy = 0;
}

// Updating this entity.
void Player::update(GLFWwindow* window, const GameState& gs, float dt) {
    bool my = false;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        this->dy += SPEED * dt;
        my = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        this->dy -= SPEED * dt;
        my = true;
    }

    if (!my) {
        if (this->dy > 0) {
            this->dy -= SPEED / 10 * dt;
        } else {
            this->dy += SPEED / 10 * dt;
        }
    }

    if (!my && this->dy > -MIN_SPEED && this->dy < MIN_SPEED)
        this->dy = 0;

    this->position().y += this->dy * dt;
}

// Providing the initial render for this entity.
void Player::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[0]["player"] = new Render(this->getPosition(),
                                      GL_DYNAMIC_DRAW,
                                      assets.getAnimation("player"),
                                      assets.getShader("res/game2d"));
}

// Rendering this entity.
void Player::render(GLFWwindow* window, Renders& renders) const {
    renders[0]["player"]->updateVertices(generateRectangle(this->getPosition()),
                                         rectangleOrder(),
                                         GL_DYNAMIC_DRAW);
}
