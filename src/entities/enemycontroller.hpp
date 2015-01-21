#ifndef _ENEMY_CONTROLLER_HPP_
#define _ENEMY_CONTROLLER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"
#include "../timer.hpp"
#include "enemy.hpp"

//////////
// Code //

// A class to control and render all of the entities.
class EnemyController : public Entity {
private:
    Timer timer;
    float nextTime;
    std::vector<Enemy*> enemies;

    // Setting the next time and resetting the timer.
    void setNextTime();

    // Adding a new enemy.
    void addEnemy(GLFWwindow*);

public:
    constexpr static int minSpawnTime =  333;
    constexpr static int maxSpawnTime = 2000;

    // CONTROLLING THINE ENEMIES.
    EnemyController();

    // Updating the set of enemies.
    void update(GLFWwindow*, const GameState&, float) override;

    // Initializing the enemy renders.
    void initRender(GLFWwindow*, const Assets&, Renders&) const override;

    // Rendering the set of enemies.
    void render(GLFWwindow*, Renders&) const override;
};

#endif
