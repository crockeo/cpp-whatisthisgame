#include "bullet.hpp"

//////////////
// Includes //
#include "controller.hpp"

//////////
// Code //

// Constructing a new bullet at a given location.
Bullet::Bullet(float x, float y, void* controller) :
        Entity(Rectangle(x, y, Bullet::width, Bullet::height)) {
    this->controller = controller;
}

// Updating this bullet.
void Bullet::update(GLFWwindow* window, const GameState& gs, float dt) {
    Controller* bc = (Controller*)controller;

    int width;
    glfwGetWindowSize(window, &width, nullptr);
    if (this->position().x > width)
        bc->mark(this);

    this->position().x += Bullet::speed * dt;
}
