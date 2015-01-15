#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

//////////////
// Includes //
#include <vector>

#include "rectangle.hpp"

//////////
// Code //

// A type to represent the internal state of the game universe.
struct GameState {
    Rectangle position;
    std::vector<Rectangle> enemies;

    // Constructing a new game state.
    GameState();
};

#endif
