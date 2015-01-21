#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"

//////////
// Code //

// A class to represent thine enemies.
class Enemy : public Entity {
private:
    int index;
    void* controller;

public:
    constexpr static float speed = 200.f;
    constexpr static float minSize = 30.f;
    constexpr static float maxSize = 50.f;

    // Creating a new enemy centered on an x & y coordinate with a given size.
    Enemy(float, float, float, int, void*);

    // Updating this enemy.
    void update(GLFWwindow*, const GameState&, float) override;
};

#endif
