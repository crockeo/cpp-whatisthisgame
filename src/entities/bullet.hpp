#ifndef _BULLET_HPP_
#define _BULLET_HPP_

//////////////
// Includes //
#include "../gamestate.hpp"

//////////
// Code //

// A class to represent a bullet entity.
class Bullet : public Entity {
public:
    constexpr static float width  = 30;
    constexpr static float height = 20;
    constexpr static float speed  = 500;

    // Constructing a new bullet at a given location.
    Bullet(float, float);

    // Updating this bullet.
    void update(GLFWwindow*, const GameState&, float) override;
};

#endif
