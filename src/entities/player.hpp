#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"
#include "../rendering.hpp"

//////////
// Code //

// A class to represent the player.
class Player : public Entity {
private:
    float dx, dy;

public:
    // Creating a new player at a given location.
    Player(float, float, float, float);

    // Updating this entity.
    void update(GLFWwindow*, const GameState&, float);

    // Rendering this entity.
    void render(GLFWwindow*, Renders&);
};

#endif
