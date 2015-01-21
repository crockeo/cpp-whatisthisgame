#ifndef _ENEMY_CONTROLLER_HPP_
#define _ENEMY_CONTROLLER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"
#include "../rendering.hpp"
#include "controller.hpp"
#include "../assets.hpp"

//////////
// Code //

// A Controller specifically for Enemies.
class EnemyController : public Controller {
private:
    float nextTime;
    Timer timer;

    // Setting the next time for the timer.
    void setNextTime();

    // Adding a new random enemy to this thingy.
    void addEnemy(GLFWwindow*);

public:
    constexpr static float minSpawnTime = 0.3f;
    constexpr static float maxSpawnTime = 2.f;

    // Creating a new, empty EnemyController.
    EnemyController();

    // Updating this enemy controller.
    void update(GLFWwindow*, const GameState&, float);

    // Setting up the render for this EnemyController.
    void initRender(GLFWwindow*, const Assets&, Renders&) const override;

    // Rendering this EnemyController.
    void render(GLFWwindow*, Renders&) const override;
};

#endif
