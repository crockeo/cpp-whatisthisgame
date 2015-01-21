#include "bulletcontroller.hpp"

//////////////
// Includes //
#include "bullet.hpp"
#include "player.hpp"

//////////
// Code //

// Updating the bullet controller.
void BulletController::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->timer.update(dt);

    Player* p = static_cast<Player*>(gs.getEntity("player"));
    if (p->isShooting() && this->timer.getTime() > BulletController::spawnRate) {
        this->timer.reset();
        this->addValue(new Bullet(p->getPosition().x + p->getPosition().w / 2,
                                  p->getPosition().y + p->getPosition().h / 2 - Bullet::height / 2,
                                  this));
    }

    this->kill();
    this->updateAll(window, gs, dt);
}

// Initializing the render for the BulletController.
void BulletController::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[1]["bullets"] = new Render(std::vector<GLfloat>(),
                                       std::vector<GLuint>(),
                                       GL_DYNAMIC_DRAW,
                                       assets.getTexture("res/bullet.png"),
                                       assets.getShader("res/game2d"));
}

// Rendering the bullet controller.
void BulletController::render(GLFWwindow* window, Renders& renders) const {
    std::vector<Rectangle> rs;
    for (auto& b: this->values)
        if (b != nullptr)
            rs.push_back(b->getPosition());

    renders[1]["bullets"]->updateVertices(generateRectangles(rs),
                                          rectangleOrders(rs.size()),
                                          GL_DYNAMIC_DRAW);
}
