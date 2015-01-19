#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"
#include "../rendering.hpp"
#include "../assets.hpp"

//////////
// Code //

// A class to represent the player.
class Player : public Entity {
private:
    float dy;

public:
    constexpr static float width  = 60;
    constexpr static float height = 60;

    // Creating a new player at a given location.
    Player(float, float);

    // Updating this entity.
    void update(GLFWwindow*, const GameState&, float);

    // Providing the initial render for this entity.
    void initRender(GLFWwindow*, const Assets&, Renders&) const override;

    // Rendering this entity.
    void render(GLFWwindow*, Renders&) const override;
};

#endif
