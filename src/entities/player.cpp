#include "player.hpp"

//////////
// Code //

#define SPEED 500
#define MIN_SPEED 1

// Creating a new player at a given location.
Player::Player(float x, float y, float w, float h) :
        Entity(Rectangle(x, y, w, h)) {
    this->dy = 0;
    this->dx = 0;
}

// Updating this entity.
void Player::update(GLFWwindow* window, const GameState& gs, float dt) {
    bool my = false, mx = false;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        this->dy += SPEED * dt;
        my = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        this->dy -= SPEED * dt;
        my = true;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        this->dx -= SPEED * dt;
        mx = true;
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        this->dx += SPEED * dt;
        mx = true;
    }

    if (!my) {
        if (this->dy > 0) {
            this->dy -= SPEED / 10 * dt;
        } else {
            this->dy += SPEED / 10 * dt;
        }
    }

    if (!mx) {
        if (this->dx > 0) {
            this->dx -= SPEED / 10 * dt;
        } else {
            this->dx += SPEED / 10 * dt;
        }
    }

    if (!my && this->dy > -MIN_SPEED && this->dy < MIN_SPEED)
        this->dy = 0;
    if (!mx && this->dx > -MIN_SPEED && this->dx < MIN_SPEED)
        this->dx = 0;

    this->position().x += this->dx * dt;
    this->position().y += this->dy * dt;
}

// Rendering this entity.
void Player::render(GLFWwindow* window, Renders& renders) const {
    renders["player"]->updateVertices(generateRectangle(this->getPosition(), 0),
                                      rectangleOrder(),
                                      GL_DYNAMIC_DRAW);
}
