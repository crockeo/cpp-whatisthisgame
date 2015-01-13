#include "assets.hpp"

//////////
// Code //

// Creating an empty set of assets.
Assets::Assets() { }

// Destructing assets.
Assets::~Assets() {
    for (auto it = this->textures.begin(); it != this->textures.end(); it++)
        delete std::get<1>(*it);
    for (auto it = this->shaders.begin(); it != this->shaders.end(); it++)
        delete std::get<1>(*it);
}

// Adding different kinds of assets.
void Assets::addTexture(std::string path) {
    this->textures[path] = new Texture(path);
}

void Assets::addShader(std::string path) {
    this->shaders[path] = new Shader(path);
}

// Getting different kind of assets.
Texture Assets::getTexture(std::string path) const { return *this->textures.at(path); }
Shader Assets::getShader(std::string path) const { return *this->shaders.at(path); }

// Loading the default set of assets into the ref.
void loadAssets(Assets& assets) {
    // Loading all of the asteroid frames (I should make spritesheet loading and
    // move them all into a single thing).
    assets.addTexture("res/asteroid/01/01.png");
    assets.addTexture("res/asteroid/01/02.png");
    assets.addTexture("res/asteroid/01/03.png");
    assets.addTexture("res/asteroid/01/04.png");
    assets.addTexture("res/asteroid/01/05.png");
    assets.addTexture("res/asteroid/01/06.png");
    assets.addTexture("res/asteroid/01/07.png");
    assets.addTexture("res/asteroid/01/08.png");
    assets.addTexture("res/asteroid/01/09.png");
    assets.addTexture("res/asteroid/01/10.png");
    assets.addTexture("res/asteroid/01/11.png");
    assets.addTexture("res/asteroid/01/12.png");
    assets.addTexture("res/asteroid/01/13.png");
    assets.addTexture("res/asteroid/01/14.png");

    // The background.
    assets.addTexture("res/background.png");

    // The bullet.
    assets.addTexture("res/bullet.png");

    // The enemy.
    assets.addTexture("res/enemy/01.png");
    assets.addTexture("res/enemy/02.png");
    assets.addTexture("res/enemy/03.png");

    // The game shader.
    assets.addShader("res/game2d");

    // The player.
    assets.addTexture("res/player/01.png");
    assets.addTexture("res/player/02.png");
    assets.addTexture("res/player/03.png");
    assets.addTexture("res/player/04.png");
}
