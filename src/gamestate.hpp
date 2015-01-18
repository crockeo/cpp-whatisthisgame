#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "rectangle.hpp"
#include "rendering.hpp"
#include "timer.hpp"

//////////
// Code //

// Some definitions to be filled in.
struct GameState;
class Entity;

// A base entity class.
class Entity {
private:
    Rectangle position;

public:
    // Constructing an entity at a given location.
    Entity(Rectangle);

    // Updating this entity.
    virtual void update(GLFWwindow*, const GameState&, float) { }

    // Rendering this entity.
    virtual void render(GLFWwindow*, Renders&) { }

    // Returning a copy of the rectangle.
    Rectangle& getPosition();
};

// A type to represent the internal state of the game universe.
struct GameState {
private:
    std::unordered_map<std::string, Entity*> entities;
    std::vector<Timer*> timers;

public:
    Rectangle position;
    std::vector<Rectangle> enemies;

    // Deleting some implicitly declared stuff.
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;

    // Constructing a new game state.
    GameState();

    // DESTROYING this GameState.
    ~GameState();

    // Adding a timer to this GameState.
    void addTimer(Timer*);

    // Updating every entity in this GameState.
    void updateAll(GLFWwindow*, const GameState&, float);

    // Rendering every entity in this GameState.
    void renderAll(GLFWwindow*, Renders&) const;

    // Adding an entity.
    void addEntity(std::string, Entity*);

    // Removing an entity.
    void removeEntity(std::string);

    // Accessing an entity.
    Entity* getEntity(std::string) const;
};

// Constructing a default GameState.
void initializeGameState(GameState&, const std::vector<Timer*>&);

#endif
