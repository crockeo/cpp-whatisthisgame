#include "gamestate.hpp"

//////////////
// Includes //
#include "entities/player.hpp"

//////////
// Code //

// Constructing an entity at a given location.
Entity::Entity(Rectangle r) :
        position(r) { }

// Returning a copy of the rectangle.
Rectangle& Entity::getPosition() { return this->position; }

// Constructing a new game state.
GameState::GameState() :
        position(0, 0, 50, 50) {
    this->enemies.push_back(Rectangle(100, 100, 50, 50));
    this->enemies.push_back(Rectangle(150, 100, 50, 50));
    this->enemies.push_back(Rectangle(100, 150, 50, 50));
    this->enemies.push_back(Rectangle(150, 150, 50, 50));
}

// DESTROYING this GameState.
GameState::~GameState() {
    for (auto it = this->entities.begin(); it != this->entities.end(); it++)
        if (std::get<1>(*it) != nullptr)
            delete std::get<1>(*it);
}

// Updating every entity in this GameState.
void GameState::updateAll(GLFWwindow* window, const GameState& gs, float dt) {
    for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
        if (std::get<1>(*it) != nullptr)
            std::get<1>(*it)->update(window, gs, dt);
    }
}

// Rendering every entity in this GameState.
void GameState::renderAll(GLFWwindow* window, Renders& renders) const {
    for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
        if (std::get<1>(*it) != nullptr)
            std::get<1>(*it)->render(window, renders);
    }
}

// Adding an entity.
void GameState::addEntity(std::string name, Entity* e) {
    this->entities[name] = e;
}

// Removing an entity.
void GameState::removeEntity(std::string name) {
    if (this->entities.find(name) != this->entities.end() && this->entities[name] != nullptr)
        delete this->entities[name];
}

// Accessing an entity.
Entity* GameState::getEntity(std::string name) const {
    if (this->entities.find(name) == this->entities.end())
        return nullptr;
    return this->entities.at(name);
}

// Constructing a default GameState.
void initializeGameState(GameState& gs) {
    gs.addEntity("player", new Player(0, 0, 50, 50));
}
