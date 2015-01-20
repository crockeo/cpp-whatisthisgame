#include "bullet.hpp"

//////////
// Code //

// Constructing a new bullet at a given location.
Bullet::Bullet(float x, float y) :
        Entity(Rectangle(x, y, Bullet::width, Bullet::height)) { }

// Updating this bullet.
void Bullet::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->position().x += Bullet::speed * dt;
}
