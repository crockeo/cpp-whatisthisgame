#include "enemy.hpp"

//////////////
// Includes //
#include <tuple>

#include "bulletcontroller.hpp"
#include "enemycontroller.hpp"
#include "../observer.hpp"
#include "../events.hpp"

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
    OM& om = OM::instance();
    EnemyController* ec = (EnemyController*)this->controller;

    this->position().x -= Enemy::speed * dt;
    if (this->position().x < -this->position().w) {
        om.alert(EnemyWinEvent());
        ec->mark(this);
    }

    BulletController* bc = (BulletController*)gs.getEntity("bulletcontroller");
    for (auto& b: bc->getValues()) {
        if (this->position().collides(b->getPosition())) {
            om.alert(EnemyShotEvent(this->position().x + this->position().w / 2,
                                    this->position().y + this->position().h / 2,
                                    b));
            ec->mark(this);
        }
    }
}
