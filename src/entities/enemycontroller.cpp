#include "enemycontroller.hpp"

//////////////
// Includes //
#include <iostream>
#include <cstdlib>

//////////
// Code //

// Setting the next time and resetting the timer.
void EnemyController::setNextTime() {
    this->timer.reset();
    this->nextTime = ((rand() + EnemyController::minSpawnTime) % EnemyController::maxSpawnTime) / 1000.f;
}

// CONTROLLING THINE ENEMIES.
EnemyController::EnemyController() :
        Entity(Rectangle(0, 0, 0, 0)) {
    this->setNextTime();
}

// Updating the set of enemies.
void EnemyController::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->timer.update(dt);
    if (this->timer.getTime() > this->nextTime) {
        // TODO: Spawn a gosh darn enemy.
        this->setNextTime();
    }

    for (auto it = this->enemies.begin(); it != this->enemies.end(); it++)
        if (*it != nullptr)
            (*it)->update(window, gs, dt);
}
