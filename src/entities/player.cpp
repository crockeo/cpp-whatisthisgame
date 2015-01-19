#include "player.hpp"

//////////
// Code //

// Creating a new player at a given location.
Player::Player(float x, float y) :
        Entity(Rectangle(x, y, Player::width, Player::height)) {
    this->dy = 0;
}

// Updating this entity.
void Player::update(GLFWwindow* window, const GameState& gs, float dt) {
    bool my = false;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        this->dy += ((this->dy < 0 ? Player::decel_speed : 0) + Player::speed) * dt;
        my = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        this->dy -= ((this->dy > 0 ? Player::decel_speed : 0) + Player::speed) * dt;
        my = true;
    }

    if (!my) {
        if (this->dy > 0) {
            this->dy -= Player::decel_speed * dt;
        } else {
            this->dy += Player::decel_speed * dt;
        }
    }

    if (!my && this->dy > -Player::min_speed && this->dy < Player::min_speed)
        this->dy = 0;

    if (this->dy >  Player::max_speed)
        this->dy =  Player::max_speed;
    if (this->dy < -Player::max_speed)
        this->dy = -Player::max_speed;

    int height;
    glfwGetWindowSize(window, nullptr, &height);

    if (this->position().y < 0) {
        this->dy /= -3;
        this->position().y = 0;
    }

    if (this->position().y + this->position().h > height) {
        this->dy /= -3;
        this->position().y = height - this->position().h;
    }

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
