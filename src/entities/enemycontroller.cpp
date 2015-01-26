#include "enemycontroller.hpp"

//////////////
// Includes //
#include <vector>

#include "../utils.hpp"
#include "enemy.hpp"

//////////
// Code //

// Setting the next time for the timer.
void EnemyController::setNextTime() {
    this->timer.reset();
    this->nextTime = randomFloat(EnemyController::minSpawnTime,
                                 EnemyController::maxSpawnTime);
}

// Adding a new random enemy to this thingy.
void EnemyController::addEnemy(GLFWwindow* window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float size      = randomFloat(Enemy::minSize, Enemy::maxSize);
    float minHeight =          size / 2;
    float maxHeight = height - size / 2;

    this->addValue(new Enemy(width,
                             randomFloat(minHeight, maxHeight),
                             size,
                             this));
}

// Creating a new, empty EnemyController.
EnemyController::EnemyController() {
    this->setNextTime();
}

// Updating this enemy controller.
void EnemyController::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->timer.update(dt);
    if (this->timer.getTime() > this->nextTime) {
        this->setNextTime();
        this->addEnemy(window);
    }

    this->kill();
    this->updateAll(window, gs, dt);
}

// Setting up the render for this EnemyController.
void EnemyController::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[2]["enemies"] = new Render(std::vector<GLfloat>(),
                                       std::vector<GLuint>(),
                                       GL_DYNAMIC_DRAW,
                                       assets.getSSAnimation("enemy"),
                                       assets.getShader("res/game2d"));
}

// Rendering this EnemyController.
void EnemyController::render(GLFWwindow* window, Renders& renders) const {
    std::vector<Rectangle> rs;
    for (auto& e: this->values)
        if (e != nullptr)
            rs.push_back(e->getPosition());

    renders[2]["enemies"]->updateVertices(generateRectangles(rs),
                                          rectangleOrders(rs.size()),
                                          GL_DYNAMIC_DRAW);
}
