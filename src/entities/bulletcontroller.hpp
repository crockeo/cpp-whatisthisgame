#ifndef _BULLET_CONTROLLER_HPP_
#define _BULLET_CONTROLLER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"
#include "../rendering.hpp"
#include "../observer.hpp"
#include "controller.hpp"
#include "../assets.hpp"

//////////
// Code //

// A specific Bullet Controller type.
class BulletController : public Controller,
                         public Listener {
private:
    Timer timer;

public:
    constexpr static float spawnRate = 0.3f;

    // Constructing this thing.
    BulletController();

    // Updating the bullet controller.
    void update(GLFWwindow*, const GameState&, float) override;

    // Initializing the render for the BulletController.
    void initRender(GLFWwindow*, const Assets&, Renders&) const override;

    // Rendering the bullet controller.
    void render(GLFWwindow*, Renders&) const override;

    // Alerting to the existence of some event.
    void alert(const Event&);
};

#endif
