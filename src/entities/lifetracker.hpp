#ifndef _LIFE_TRACKER_HPP_
#define _LIFE_TRACKER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"
#include "../rendering.hpp"
#include "../observer.hpp"
#include "../assets.hpp"

//////////
// Code //

// Keeping track of the player's life.
class LifeTracker : public Listener,
                    public Entity {
private:
    int life;

public:
    constexpr static int standardLives = 5;

    // Creating a LifeTracker with a given amount of life.
    LifeTracker(int);

    // Creating a LifeTracker with the standard amount of life.
    LifeTracker();

    // Initializing the render.
    void initRender(GLFWwindow*, const Assets&, Renders&) const override;

    // Rendering.
    void render(GLFWwindow*, Renders&) const override;

    // Alerting the LifeTracker of a given event.
    void alert(const Event&) override;
};

#endif
