#include "config.hpp"

//////////
// Code //

// Initializing the config.
Config::Config(int windowWidth, int windowHeight, bool fullscreen) {
    this->windowWidth  = windowWidth;
    this->windowHeight = windowHeight;
    this->fullscreen   = fullscreen;
}
