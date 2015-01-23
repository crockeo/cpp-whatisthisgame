#include "bulletcontroller.hpp"

//////////////
// Includes //
#include "../events.hpp"
#include "bullet.hpp"
#include "player.hpp"

//////////
// Code //

// Constructing this thing.
BulletController::BulletController() {
    OM& om = OM::instance();

    om.addListener(Event::BULLET_SHOOT_EVENT, this);
    om.addListener(Event::ENEMY_SHOT_EVENT, this);
}

// Updating the bullet controller.
void BulletController::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->timer.update(dt);
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

// Alerting to the existence of some event.
void BulletController::alert(const Event& e) {
    if (e.getType() == Event::BULLET_SHOOT_EVENT) {
        const BulletShootEvent& bse = dynamic_cast<const BulletShootEvent&>(e);

        if (this->timer.getTime() > BulletController::spawnRate) {
            this->timer.reset();
            this->addValue(new Bullet(bse.x, bse.y - Bullet::height / 2, bse.dy / 8, this));
        }
    } else if (e.getType() == Event::ENEMY_SHOT_EVENT) {
        const EnemyShotEvent& ese = dynamic_cast<const EnemyShotEvent&>(e);
        this->mark(static_cast<Entity*>(ese.ptr));
    }
}
