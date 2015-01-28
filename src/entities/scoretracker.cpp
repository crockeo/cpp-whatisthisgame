#include "scoretracker.hpp"

//////////////
// Includes //
#include <sstream>

//////////
// Code //

// Constructing a score tracker.
ScoreTracker::ScoreTracker() :
        Entity(Rectangle(0, 0, 0, 0)) {
    this->score = 0;
}

// Updating this entity.
void ScoreTracker::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->timer.update(dt);
    if (timer.getTime() > ScoreTracker::scoreRate) {
        this->timer.reset();
        this->score++;
    }
}

// Initializing the render for this thingy.
void ScoreTracker::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[0]["score"] = new FontRender(
        assets.getShader("res/text"),
        assets.getFont("res/speculum.ttf")
    );
}

// Updating the render for this thingy.
void ScoreTracker::render(GLFWwindow* window, Renders& renders) const {
    std::ostringstream str;
    str << "Score: "
        << this->score;

    renders[0]["score"]->updateText(str.str(), 10, 10);
}
