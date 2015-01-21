#include "enemy.hpp"

//////////////
// Includes //
#include "enemycontroller.hpp"

//////////
// Code //

// Creating a new enemy centered on an x & y coordinate with a given size.
Enemy::Enemy(float x, float y, float size, int index, void* controller) :
        Entity(Rectangle(x - size / 2,
                         y - size / 2,
                         size,
                         size)) {
    this->index = index;
    this->controller = controller;
}

// Updating this enemy.
void Enemy::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->position().x -= Enemy::speed * dt;
    if (this->position().x < -this->position().w)
        ((EnemyController*)this->controller)->mark(this->index);

    // TODO: Dying on bullet collision.
}
