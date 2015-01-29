#include "gamestate.hpp"

//////////////
// Includes //
#include "entities/explodecontroller.hpp"
#include "entities/bulletcontroller.hpp"
#include "entities/enemycontroller.hpp"
#include "entities/scoretracker.hpp"
#include "entities/lifetracker.hpp"
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
GameState::GameState() { }

// DESTROYING this GameState.
GameState::~GameState() {
    // Dear future programmer,
    //
    //   I'm sorry. I am really, truly sorry. The following code should never,
    // ever have made it into a commit. I have a list of excuses (I was tired,
    // I was near the end of the project, etc.) but none of them can atone for
    // this hanous sin I have commited. It was segfaulting and-- and I just
    // didn't know what to do. So I slapped a bunch of dynamic_casts everywhere
    // and it worked. I'm so, so sorry. Please forgive me, future programmer.
    //

    for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
        if (std::get<1>(*it) != nullptr) {
            std::string name = std::get<0>(*it);
            if (name.compare("explodecontroller") == 0)
                delete dynamic_cast<ExplodeController*>(std::get<1>(*it));
            else if (name.compare("bulletcontroller") == 0)
                delete dynamic_cast<BulletController*>(std::get<1>(*it));
            else if (name.compare("enemycontroller") == 0)
                delete dynamic_cast<EnemyController*>(std::get<1>(*it));
            else if (name.compare("scoretracker") == 0)
                delete dynamic_cast<ScoreTracker*>(std::get<1>(*it));
            else if (name.compare("lifetracker") == 0)
                delete dynamic_cast<LifeTracker*>(std::get<1>(*it));
            else if (name.compare("background") == 0)
                delete dynamic_cast<Background*>(std::get<1>(*it));
            else if (name.compare("player") == 0)
                delete dynamic_cast<Player*>(std::get<1>(*it));
        }
    }
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
    for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
        if (std::get<1>(*it) != nullptr)
            std::get<1>(*it)->initRender(window, assets, renders);
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
    gs.addEntity("player", new Player(10, height / 2 - Player::height / 2));
}
