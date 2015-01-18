#ifndef _BACKGROUND_HPP_
#define _BACKGROUND_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../gamestate.hpp"
#include "../rendering.hpp"
#include "../assets.hpp"

//////////
// Code //

// The class that represents the background.
class Background : public Entity {
private:
    // Updating the size of the background.
    void updateSize(GLFWwindow*);

public:
    // Creating a new background from GLFWwindow.
    Background();

    // Updating this entity.
    void update(GLFWwindow*, const GameState&, float);

    // Providing the initial render for this entity.
    void initRender(GLFWwindow*, const Assets&, Renders&) const override;

    // Rendering this entity.
    void render(GLFWwindow*, Renders&) const override;
};

#endif
