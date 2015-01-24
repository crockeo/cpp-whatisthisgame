#include "explodecontroller.hpp"

//////////////
// Includes //
#include "../events.hpp"

//////////
// Code //

// Constructing an explosion at a given location, with a given size, that
// should exist for a given period of time.
Explode::Explode(float x, float y, float w, float h, float live, ExplodeController* controller) :
        Entity(Rectangle(x - w / 2,
                         y - h / 2,
                         w, h)) {
    this->controller = controller;
    this->isAlive = true;
    this->live = live;
}

// Updating this explosion.
void Explode::update(GLFWwindow* window, const GameState& gs, float dt) {
    if (this->isAlive) {
        this->timer.update(dt);
        if (timer.getTime() > this->live) {
            this->controller->mark(this);
            this->isAlive = false;
            this->timer.reset();
        }
    }
}

// Constructing a new ExplodeController and registering it with the
// Observer.
ExplodeController::ExplodeController() {
    OM::instance().addListener(Event::ENEMY_SHOT_EVENT, this);
}

// Updating the set of explosions and the controller itself.
void ExplodeController::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->kill();
    this->updateAll(window, gs, dt);
}

// Initializing the explosion renders.
void ExplodeController::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[2]["explosions"] = new Render(std::vector<GLfloat>(),
                                          std::vector<GLuint>(),
                                          GL_DYNAMIC_DRAW,
                                          assets.getAnimation("explosion"),
                                          assets.getShader("res/game2d"));
}

// Updating the renders.
void ExplodeController::render(GLFWwindow* window, Renders& renders) const {
    std::vector<Rectangle> rectangles;
    for (auto& e: this->values)
        rectangles.push_back(e->getPosition());

    renders[2]["explosions"]->updateVertices(generateRectangles(rectangles),
                                             rectangleOrders(rectangles.size()),
                                             GL_DYNAMIC_DRAW);
}

// Alerting this class to an event.
void ExplodeController::alert(const Event& e) {
    if (e.getType() == Event::ENEMY_SHOT_EVENT) {
        const EnemyShotEvent& ese = dynamic_cast<const EnemyShotEvent&>(e);
        this->addValue(new Explode(ese.x, ese.y, ese.size, ese.size, 1.f, this));
    }
}
