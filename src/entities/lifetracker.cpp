#include "lifetracker.hpp"

//////////////
// Includes //
#include <sstream>

#include "../rectangle.hpp"

//////////
// Code //

// Creating a LifeTracker with a given amount of life.
LifeTracker::LifeTracker(int life) :
        Entity(Rectangle(0, 0, 0, 0)) {
    OM::instance().addListener(Event::ENEMY_WIN_EVENT, this);
    this->life = life;
}

// Creating a LifeTracker with the standard amount of life.
LifeTracker::LifeTracker() :
        LifeTracker(LifeTracker::standardLives) { }

// Initializing the render.
void LifeTracker::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[0]["life"] = new FontRender(
        assets.getShader("res/text"),
        assets.getFont("res/speculum.ttf")
    );
}

// Rendering.
void LifeTracker::render(GLFWwindow* window, Renders& renders) const {
    std::ostringstream str;
    str << "Lives: "
        << this->life;

    renders[0]["life"]->updateText(
        str.str(),
        10, 50
    );
}

// Alerting the LifeTracker of a given event.
void LifeTracker::alert(const Event& e) {
    if (e.getType() == Event::ENEMY_WIN_EVENT)
        this->life--;
}
