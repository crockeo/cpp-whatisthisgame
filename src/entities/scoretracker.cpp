#include "scoretracker.hpp"

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
