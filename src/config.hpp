#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

//////////
// Code //

// A configuration for the game engine.
struct Config {
    int windowWidth, windowHeight;
    bool fullscreen;

    // Initializing the config.
    Config(int, int, bool);
};

#endif
