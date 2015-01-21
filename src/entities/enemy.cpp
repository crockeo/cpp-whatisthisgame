#include "enemy.hpp"

//////////////
// Includes //
#include <tuple>

#include "bulletcontroller.hpp"
#include "enemycontroller.hpp"

//////////
// Code //

// Creating a new enemy centered on an x & y coordinate with a given size.
Enemy::Enemy(float x, float y, float size, void* controller) :
        Entity(Rectangle(x - size / 2,
                         y - size / 2,
                         size,
                         size)) {
    this->controller = controller;
}

// Updating this enemy.
void Enemy::update(GLFWwindow* window, const GameState& gs, float dt) {
    EnemyController* ec = (EnemyController*)this->controller;
    this->position().x -= Enemy::speed * dt;
    if (this->position().x < -this->position().w)
        ec->mark(this);

    BulletController* bc = (BulletController*)gs.getEntity("bulletcontroller");
    auto bullets = bc->getValues();

    for (auto& b: bullets) {
        if (this->position().collides(b->getPosition())) {
            bc->mark(b);
            ec->mark(this);
        }
    }
}
