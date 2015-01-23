#ifndef _EXPLODE_CONTROLLER_HPP_
#define _EXPLODE_CONTROLLER_HPP_

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

// Type declarations.
class ExplodeController;
class Explode;

// A single explosion.
class Explode : public Entity {
private:
    ExplodeController* controller;
    bool isAlive;
    Timer timer;
    float live;

public:
    // Constructing an explosion at a given location, with a given size, that
    // should exist for a given period of time.
    Explode(float, float, float, float, float, ExplodeController*);

    // Updating this explosion.
    void update(GLFWwindow*, const GameState&, float);
};

// Controlling every explosion.
class ExplodeController : public Controller,
                          public Listener {
public:
    // Constructing a new ExplodeController and registering it with the
    // Observer.
    ExplodeController();

    // Updating the set of explosions and the controller itself.
    void update(GLFWwindow*, const GameState&, float);

    // Initializing the explosion renders.
    void initRender(GLFWwindow*, const Assets&, Renders&) const;

    // Updating the renders.
    void render(GLFWwindow*, Renders&) const;

    // Alerting this class to an event.
    void alert(const Event&);
};

#endif
