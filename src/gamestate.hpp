#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "rectangle.hpp"
#include "rendering.hpp"
#include "assets.hpp"
#include "timer.hpp"

//////////
// Code //

// Some definitions to be filled in.
struct GameState;
class Entity;

// A base entity class.
class Entity {
private:
    Rectangle pos;

public:
    // Constructing an entity at a given location.
    Entity(Rectangle);

    // Default virtual destructor.
    virtual ~Entity() { }

    // Updating this entity.
    virtual void update(GLFWwindow*, const GameState&, float) { }

    // Initializing the render for this entity.
    virtual void initRender(GLFWwindow*, const Assets&, Renders&) const { }

    // Rendering this entity.
    virtual void render(GLFWwindow*, Renders&) const { }

    // Returning a copy of the rectangle.
    Rectangle getPosition() const;

    // Returning a reference to the rectangle.
    Rectangle& position();
};

// A type to represent the internal state of the game universe.
struct GameState {
private:
    std::unordered_map<std::string, Entity*> entities;
    std::vector<std::shared_ptr<Timer>> timers;

public:
    // Deleting some implicitly declared stuff.
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;

    // Constructing a new game state.
    GameState();

    // DESTROYING this GameState.
    ~GameState();

    // Adding a timer to this GameState.
    void addTimer(std::shared_ptr<Timer>);

    // Updating every entity in this GameState.
    void updateAll(GLFWwindow*, const GameState&, float);

    // Initializing all of the renders for the GameState.
    void initRenderAll(GLFWwindow*, const Assets&, Renders&) const;

    // Rendering every entity in this GameState.
    void renderAll(GLFWwindow*, const Assets&, Renders&) const;

    // Adding an entity.
    void addEntity(std::string, Entity*);

    // Removing an entity.
    void removeEntity(std::string);

    // Accessing an entity.
    Entity* getEntity(std::string) const;
};

// Constructing a default GameState.
void initializeGameState(GLFWwindow*, GameState&, const std::vector<std::shared_ptr<Timer>>&);

#endif
