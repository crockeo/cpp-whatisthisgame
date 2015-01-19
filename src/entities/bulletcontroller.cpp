#include "bulletcontroller.hpp"

//////////////
// Includes //
#include "player.hpp"

//////////
// Code //

// Creating a new, empty BulletContainer.
BulletController::BulletController() :
        Entity(Rectangle(0, 0, 50, 50)) { }

// Updating the BulletController.
void BulletController::update(GLFWwindow* window, const GameState& gs, float dt) {
    Player* p = (Player*)gs.getEntity("player");

    if (p->isShooting())
        this->position().x = 50;
    else
        this->position().x = 0;
}

// Setting up the first render for the BulletController.
void BulletController::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[0]["bulletcontroller"] = new Render(this->getPosition(),
                                                GL_DYNAMIC_DRAW,
                                                assets.getTexture("res/bullet.png"),
                                                assets.getShader("res/game2d"));
}

// Setting up the first render for the BulletController.
void BulletController::render(GLFWwindow* window, Renders& renders) const {
    renders[0]["bulletcontroller"]->updateVertices(generateRectangle(this->getPosition()),
                                                   rectangleOrder(),
                                                   GL_DYNAMIC_DRAW);
}
