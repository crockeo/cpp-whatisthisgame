#ifndef _BULLET_HPP_
#define _BULLET_HPP_

//////////////
// Includes //
#include "../gamestate.hpp"

//////////
// Code //

// Dear future me (and any other developers reading this),
//
//  I'm really, really sorry for using a void* pointer in C++. I understand that
// they're kind of really horrible. But I just didn't want to deal with doing
// things the right way.

// A class to represent a bullet entity.
class Bullet : public Entity {
private:
    float dy;
    void* controller;

public:
    constexpr static float width  = 32;
    constexpr static float height = 16;
    constexpr static float speed  = 500;

    // Constructing a new bullet at a given location.
    Bullet(float, float, float dy, void*);

    // Updating this bullet.
    void update(GLFWwindow*, const GameState&, float) override;
};

#endif
