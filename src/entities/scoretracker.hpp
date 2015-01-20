#ifndef _SCORE_TRACKER_HPP_
#define _SCORE_TRACKER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"

//////////
// Code //

// A class to keep track of the score.
class ScoreTracker : public Entity {
private:
    Timer timer;
    int score;

public:
    constexpr static float scoreRate = 0.8f;

    // Constructing a score tracker.
    ScoreTracker();

    // Updating this entity.
    void update(GLFWwindow*, const GameState&, float);
};

#endif
