#include "controller.hpp"

//////////
// Code //

// Updating every single entity in this controller.
void Controller::updateAll(GLFWwindow* window, const GameState& gs, float dt) {
    for (auto& v: this->values)
        if (v != nullptr)
            v->update(window, gs, dt);
}

// Constructing a Controller with a given Texture, Shader, and render type.
Controller::Controller() :
        Entity(Rectangle(0, 0, 0, 0)) { }

// Destroying this controller.
Controller::~Controller() {
    // TODO: DESTROY THIS CONTROLLER.
}

// Marking a pointer.
void Controller::mark(Entity* e) { this->marks.insert(e); }

// Cleaning up everything in the values.
void Controller::kill() {
    for (auto& m: this->marks) {
        this->values.erase(this->values.find(m));
        delete m;
    }

    this->marks.clear();
}

// Adding a value.
void Controller::addValue(Entity* e) {
    if (e != nullptr)
        this->values.insert(e);
}

// Getting the set of values from this controller.
std::unordered_set<Entity*> Controller::getValues() { return this->values; }
