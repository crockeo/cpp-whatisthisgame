#include "bulletcontroller.hpp"

//////////////
// Includes //
#include <algorithm>

#include "player.hpp"

//////////
// Code //

// Creating a new, empty BulletContainer.
BulletController::BulletController() :
        Entity(Rectangle(0, 0, 50, 50)) { }

// Destroying this BulletController.
BulletController::~BulletController() {
    for_each(this->bullets.begin(), this->bullets.end(),
        [](Bullet* b) {
            if (b != nullptr)
                delete b;
        }
    );
}

// Marking a given index to be killed off.
void BulletController::mark(int index) {
    this->marks.insert(index);
}

// Killing off all of the marked bullets.
void BulletController::kill() {
    for (auto it = this->marks.begin(); it != this->marks.end(); it++) {
        delete bullets.at(*it);
        bullets.at(*it) = nullptr;
    }

    this->marks.clear();
}

// Updating the BulletController.
void BulletController::update(GLFWwindow* window, const GameState& gs, float dt) {
    Player* p = (Player*)gs.getEntity("player");

    this->timer.update(dt);

    if (timer.getTime() > BulletController::spawnRate && p->isShooting()) {
        timer.reset();
        this->bullets.push_back(new Bullet(p->getPosition().x + p->getPosition().w / 2,
                                           p->getPosition().y + p->getPosition().h / 2 - Bullet::height / 2,
                                           this->bullets.size(),
                                           this));
    }

    this->kill();

    for (auto it = this->bullets.begin(); it != this->bullets.end(); it++)
        if (*it != nullptr)
            (*it)->update(window, gs, dt);
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
    std::vector<Rectangle> rs;
    for (auto it = this->bullets.begin(); it != this->bullets.end(); it++)
        if (*it != nullptr)
            rs.push_back((*it)->getPosition());

    renders[0]["bulletcontroller"]->updateVertices(generateRectangles(rs),
                                                   rectangleOrders(rs.size()),
                                                   GL_DYNAMIC_DRAW);
}
