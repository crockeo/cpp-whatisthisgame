#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_set>

#include "../res/texture.hpp"
#include "../res/shader.hpp"
#include "../gamestate.hpp"
#include "../rendering.hpp"
#include "../assets.hpp"

//////////
// Code //

// A generic controller class.
class Controller {
protected:
    std::unordered_set<Entity*> values;
    std::unordered_set<Entity*> marks;

    // Updating every single entity in this controller.
    void updateAll(GLFWwindow*, const GameState&, float);

public:
    // Constructing a Controller with a given Texture, Shader, and render type.
    Controller();

    // Destroying this controller.
    ~Controller();

    // Marking a pointer.
    void mark(Entity*);

    // Cleaning up everything in the values.
    void kill();

    // Adding a value.
    void addValue(Entity*);
};

#endif
