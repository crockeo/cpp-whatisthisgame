#ifndef _BULLET_CONTROLLER_HPP_
#define _BULLET_CONTROLLER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"
#include "../rendering.hpp"
#include "../assets.hpp"
#include "bullet.hpp"

//////////
// Code //

// An entity that controls the set of bullets.
class BulletController : public Entity {
private:
    std::vector<Bullet*> bullets;

public:
    // Creating a new, empty BulletController.
    BulletController();

    // Destroying this BulletController.
    ~BulletController();

    // Updating the BulletController.
    void update(GLFWwindow*, const GameState&, float) override;

    // Setting up the first render for the BulletController.
    void initRender(GLFWwindow*, const Assets&, Renders&) const override;

    // Setting up the first render for the BulletController.
    void render(GLFWwindow*, Renders&) const override;
};

#endif
