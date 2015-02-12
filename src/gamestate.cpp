#include "gamestate.hpp"

//////////////
// Includes //
#include "entities/explodecontroller.hpp"
#include "entities/bulletcontroller.hpp"
#include "entities/enemycontroller.hpp"
#include "entities/scoretracker.hpp"
#include "entities/lifetracker.hpp"
#include "entities/background.hpp"
#include "entities/fpscounter.hpp"
#include "entities/player.hpp"

#include "config.hpp"

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
GameState::GameState() { }

// DESTROYING this GameState.
GameState::~GameState() {
    for (auto& e: this->entities)
        if (std::get<1>(e) != nullptr)
            delete std::get<1>(e);
}

// Adding a timer to this GameState.
void GameState::addTimer(std::shared_ptr<Timer> timer) { this->timers.push_back(timer); }

// Updating every entity in this GameState.
void GameState::updateAll(GLFWwindow* window, const GameState& gs, float dt) {
    if (this->entities.find("lifetracker") != this->entities.end()) {
        LifeTracker* lt = dynamic_cast<LifeTracker*>(this->entities.at("lifetracker"));

        if (lt->alive()) {
            for (auto it = this->timers.begin(); it != this->timers.end(); it++)
                if (*it != nullptr)
                    (*it)->update(dt);

            for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
                if (std::get<1>(*it) != nullptr)
                    std::get<1>(*it)->update(window, gs, dt);
            }
        }
    }
}

// Initializing all of the renders for the GameState.
void GameState::initRenderAll(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[0]["lost"] = new FontRender(assets.getShader("res/text"), assets.getFont("res/cubic.ttf"));

    for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
        if (std::get<1>(*it) != nullptr)
            std::get<1>(*it)->initRender(window, assets, renders);
    }
}

// Rendering every entity in this GameState.
void GameState::renderAll(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    if (this->entities.find("lifetracker") != this->entities.end()) {
        LifeTracker* lt = dynamic_cast<LifeTracker*>(this->entities.at("lifetracker"));

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        if (!lt->alive()) {
            renders[0]["lost"]->updateText(
                "You lost.",
                width  / 2 - assets.getFont("res/cubic.ttf").displayWidth ("You lost.") / 2,
                height / 2 - assets.getFont("res/cubic.ttf").displayHeight("You lost.") / 2
            );
        }
    }

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
void initializeGameState(GLFWwindow* window, GameState& gs, const std::vector<std::shared_ptr<Timer>>& timers) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    for (auto it = timers.begin(); it != timers.end(); it++)
        gs.addTimer(*it);

    gs.addEntity("explodecontroller", new ExplodeController());
    gs.addEntity("bulletcontroller", new BulletController());
    gs.addEntity("enemycontroller", new EnemyController());
    gs.addEntity("scoretracker", new ScoreTracker());
    gs.addEntity("lifetracker", new LifeTracker());
    gs.addEntity("background", new Background());
    if (DEBUG)
        gs.addEntity("fpscounter", new FpsCounter());
    gs.addEntity("player", new Player(10, height / 2 - Player::height / 2));
}
