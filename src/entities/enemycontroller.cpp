#include "enemycontroller.hpp"

//////////////
// Includes //
#include <iostream>
#include <cstdlib>

#include "../rectangle.hpp"
#include "../utils.hpp"

//////////
// Code //

// Setting the next time and resetting the timer.
void EnemyController::setNextTime() {
    this->timer.reset();
    this->nextTime = ((rand() + EnemyController::minSpawnTime) % EnemyController::maxSpawnTime) / 1000.f;
}

// Adding a new enemy.
void EnemyController::addEnemy(GLFWwindow* window) {
    float size = randomFloat(Enemy::minSize, Enemy::maxSize);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float minY =          size / 2;
    float maxY = height - size / 2;

    this->enemies.push_back(new Enemy(width + size / 2, randomFloat(minY, maxY), size));
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
        this->addEnemy(window);
        this->setNextTime();
    }

    // TODO: Mark and kill enemy folk.

    for (auto it = this->enemies.begin(); it != this->enemies.end(); it++)
        if (*it != nullptr)
            (*it)->update(window, gs, dt);
}

// Initializing the enemy renders.
void EnemyController::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[1]["enemies"] = new Render(std::vector<GLfloat>(),
                                       std::vector<GLuint>(),
                                       GL_DYNAMIC_DRAW,
                                       assets.getTexture("res/enemy/01.png"),
                                       assets.getShader("res/game2d"));
}

// Rendering the set of enemies.
void EnemyController::render(GLFWwindow* window, Renders& renders) const {
    std::vector<Rectangle> rectangles;
    for (auto it = this->enemies.begin(); it != this->enemies.end(); it++)
        if (*it != nullptr)
            rectangles.push_back((*it)->getPosition());

    renders[1]["enemies"]->updateVertices(generateRectangles(rectangles),
                                          rectangleOrders(rectangles.size()),
                                          GL_DYNAMIC_DRAW);
}
