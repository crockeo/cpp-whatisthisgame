#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_set>

#include "../gamestate.hpp"
#include "../rendering.hpp"
#include "../assets.hpp"

//////////
// Code //

// A generic controller class.
class Controller : public Entity {
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

    // Getting the set of values from this controller.
    std::unordered_set<Entity*> getValues();

    // Virtual functions for the entity.
    virtual void update     (GLFWwindow*, const GameState&, float   )       override = 0;
    virtual void initRender (GLFWwindow*, const Assets&   , Renders&) const override = 0;
    virtual void render     (GLFWwindow*,                   Renders&) const override = 0;
};

#endif
