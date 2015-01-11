#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

//////////
// Code //

// A type to represent the internal state of the game universe.
struct GameState {
    float x, y;
    float w, h;

    // Constructing a new game state.
    GameState(float, float, float, float);
};

#endif
