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
    bool shooting;
    float dy;

public:
    constexpr static float speed       = 2250;
    constexpr static float decel_speed = speed * 2;
    constexpr static float max_speed   = speed / 4;
    constexpr static float min_speed   = 20;
    constexpr static float width       = 60;
    constexpr static float height      = 60;

    // Creating a new player at a given location.
    Player(float, float);

    // Updating this entity.
    void update(GLFWwindow*, const GameState&, float);

    // Providing the initial render for this entity.
    void initRender(GLFWwindow*, const Assets&, Renders&) const override;

    // Rendering this entity.
    void render(GLFWwindow*, Renders&) const override;

    // Checking if the player is actively shooting.
    bool isShooting() const;

    // Getting the current delta y of the player.
    float getDY() const;
};

#endif
