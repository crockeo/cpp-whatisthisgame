#include "enemy.hpp"

// Creating a new enemy centered on an x & y coordinate with a given size.
Enemy::Enemy(float x, float y, float size) :
        Entity(Rectangle(x - size / 2,
                         y - size / 2,
                         size,
                         size)) { }

// Updating this enemy.
void Enemy::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->position().x -= Enemy::speed * dt;
}
