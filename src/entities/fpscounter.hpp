#ifndef _FPS_COUNTER_HPP_
#define _FPS_COUNTER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"
#include "../rendering.hpp"

//////////
// Code //

// A class to represent an FPS counter.
class FpsCounter : public Entity {
private:
    float fps;

public:
    // Starting the FPS counter.
    FpsCounter();

    // Updating.
    void update(GLFWwindow*, const GameState&, float dt) override;

    // Initializing rendering.
    void initRender(GLFWwindow*, const Assets&, Renders&) const override;

    // Rendering shit.
    void render(GLFWwindow*, Renders&) const override;
};

#endif
