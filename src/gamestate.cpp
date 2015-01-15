#include "gamestate.hpp"

//////////
// Code //

// Constructing a new game state.
GameState::GameState() :
        position(0, 0, 50, 50) {
    this->enemies.push_back(Rectangle(100, 100, 50, 50));
    this->enemies.push_back(Rectangle(150, 100, 50, 50));
    this->enemies.push_back(Rectangle(100, 150, 50, 50));
    this->enemies.push_back(Rectangle(150, 150, 50, 50));
}
