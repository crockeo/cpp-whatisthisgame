#include "assets.hpp"

//////////
// Code //

// Creating an empty set of assets.
Assets::Assets() { }

// Destructing assets.
Assets::~Assets() { }

// Adding different kinds of assets.
void Assets::addTexture(std::string path) { }
void Assets::addShader(std::string path) { }

// Getting different kind of assets.
Texture Assets::getTexture(std::string path) const { return *this->textures.at(path); }
Shader Assets::getShader(std::string path) const { return *this->shaders.at(path); }

// Loading the default set of assets into the ref.
void loadAssets(Assets& assets) {
    // TODO: Add all of the assets.
}
