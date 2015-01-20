#include "bullet.hpp"

//////////////
// Includes //
#include "bulletcontroller.hpp"

//////////
// Code //

// Constructing a new bullet at a given location.
Bullet::Bullet(float x, float y, int index, void* bulletcontroller) :
        Entity(Rectangle(x, y, Bullet::width, Bullet::height)) {
    this->index = index;
    this->bulletcontroller = bulletcontroller;
}

// Updating this bullet.
void Bullet::update(GLFWwindow* window, const GameState& gs, float dt) {
    BulletController* bc = (BulletController*)bulletcontroller;

    int width;
    glfwGetWindowSize(window, &width, nullptr);
    if (this->position().x > width)
        bc->mark(this->index);

    this->position().x += Bullet::speed * dt;
}
