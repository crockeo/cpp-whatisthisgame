#include "assets.hpp"

//////////
// Code //

// Creating an empty set of assets.
Assets::Assets() { }

// Adding different kinds of assets.
void Assets::addSpritesheet(std::string path, int cols, int rows) {
    if (this->textures.find(path) == this->textures.end())
        this->addTexture(path);
    this->spritesheets[path] = std::unique_ptr<Spritesheet>(new Spritesheet(this->getTexture(path), cols, rows));
}

void Assets::addSSAnimation(std::string name, Spritesheet ss, float frameLength, bool loop) {
    this->ssAnimations[name] = std::unique_ptr<SSAnimation>(new SSAnimation(ss, frameLength, loop));
}

void Assets::addSSAnimation(std::string name, Spritesheet ss, float frameLength) {
    this->addSSAnimation(name, ss, frameLength, true);
}

void Assets::addAnimation(std::string path, std::vector<Texture> textures, float frameLength, bool doesLoop) {
    this->animations[path] = std::unique_ptr<Animation>(new Animation(textures, frameLength, doesLoop));
}

void Assets::addAnimation(std::string path, std::vector<Texture> textures, float frameLength) {
    this->addAnimation(path, textures, frameLength, true);
}

void Assets::addTexture(std::string path) {
    this->textures[path] = std::unique_ptr<Texture>(new Texture(path));
}

void Assets::addShader(std::string path) {
    this->shaders[path] = std::unique_ptr<Shader>(new Shader(path));
}

// Getting the vector of animation timers.
std::vector<std::shared_ptr<Timer>> Assets::getAnimationTimers() const {
    std::vector<std::shared_ptr<Timer>> timers;

    for (auto it = this->animations.begin(); it != this->animations.end(); it++)
        if (std::get<1>(*it) != nullptr)
            timers.push_back(std::get<1>(*it)->getTimer());
    for (auto it = this->ssAnimations.begin(); it != this->ssAnimations.end(); it++)
        if (std::get<1>(*it) != nullptr)
            timers.push_back(std::get<1>(*it)->getTimer());

    //for (const auto a&: this->animations)
        //if (std::get<1>(a) != nullptr)
            //timers.push_back(std::get<1>(a)->getTimer());

    //for (const auto a&: this->ssAnimations)
        //if (std::get<1>(a) != nullptr)
            //timers.push_back(std::get<1>(a)->getTimer());

    return timers;
}

// Getting different kind of assets.
const Spritesheet& Assets::getSpritesheet(std::string path) const { return *this->spritesheets.at(path); }
const SSAnimation& Assets::getSSAnimation(std::string path) const { return *this->ssAnimations.at(path); }
const Animation& Assets::getAnimation(std::string path)     const { return *this->animations.at(path);   }
const Texture& Assets::getTexture(std::string path)         const { return *this->textures.at(path);     }
const Shader& Assets::getShader(std::string path)           const { return *this->shaders.at(path);      }

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
    assets.addSpritesheet("res/enemy.png", 3, 1);
    assets.addSSAnimation(
        "enemy",
        assets.getSpritesheet("res/enemy.png"),
        0.2f
    );

    // The game shader.
    assets.addShader("res/game2d");

    // The player.
    assets.addSpritesheet("res/player.png", 2, 2);
    assets.addSSAnimation(
        "player",
        assets.getSpritesheet("res/player.png"),
        0.2f
    );

    // Adding the explosions!
    assets.addSpritesheet("res/explosion.png", 2, 1);
    assets.addSSAnimation(
        "explosion",
        assets.getSpritesheet("res/explosion.png"),
        0.4f
    );
}
