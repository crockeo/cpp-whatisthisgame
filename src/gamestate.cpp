#include "gamestate.hpp"

//////////////
// Includes //
#include "entities/background.hpp"
#include "entities/player.hpp"

//////////
// Code //

// Constructing an entity at a given location.
Entity::Entity(Rectangle r) :
        pos(r) { }

// Returning a copy of the rectangle.
Rectangle Entity::getPosition() const { return this->pos; }

// Returning a reference to the rectangle.
Rectangle& Entity::position() { return this->pos; }

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

// Adding a timer to this GameState.
void GameState::addTimer(Timer* timer) { this->timers.push_back(timer); }

// Updating every entity in this GameState.
void GameState::updateAll(GLFWwindow* window, const GameState& gs, float dt) {
    for (auto it = this->timers.begin(); it != this->timers.end(); it++)
        if (*it != nullptr)
            (*it)->update(dt);

    for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
        if (std::get<1>(*it) != nullptr)
            std::get<1>(*it)->update(window, gs, dt);
    }
}

// Initializing all of the renders for the GameState.
void GameState::initRenderAll(GLFWwindow* window, Renders& renders) const {
    for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
        if (std::get<1>(*it) != nullptr)
            std::get<1>(*it)->initRender(window, renders);
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
void initializeGameState(GameState& gs, const std::vector<Timer*>& timers) {
    for (auto it = timers.begin(); it != timers.end(); it++)
        gs.addTimer(*it);

    gs.addEntity("background", new Background());
    gs.addEntity("player", new Player(0, 0, 50, 50));
}
