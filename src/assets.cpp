#include "assets.hpp"

//////////////
// Includes //
#include <fstream>

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

void Assets::addFont(std::string path, int pnt) {
    this->fonts[path] = std::unique_ptr<Font>(new Font(path, pnt));
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

    return timers;
}

// Getting different kind of assets.
const Spritesheet& Assets::getSpritesheet(std::string path) const { return *this->spritesheets.at(path); }
const SSAnimation& Assets::getSSAnimation(std::string path) const { return *this->ssAnimations.at(path); }
const Animation& Assets::getAnimation(std::string path)     const { return *this->animations.at(path);   }
const Texture& Assets::getTexture(std::string path)         const { return *this->textures.at(path);     }
const Shader& Assets::getShader(std::string path)           const { return *this->shaders.at(path);      }
const Font& Assets::getFont(std::string path)               const { return *this->fonts.at(path);        }

// Loading an AssetLoads from an istream.
AssetLoads::AssetLoads(std::istream&& in) throw(std::string) {
    if (!in.good())
        throw std::string("Invalid input stream.");

    try {
        while (!in.eof()) {
            std::string prefix;
            in >> prefix;

            if (prefix.compare("#") == 0) {
                char c;
                do {
                    c = in.get();
                } while (c != '\n' && c != '\r');

                continue;
            }

            if (prefix.compare("shader") == 0) {
                std::string path;
                in >> path;
                this->shaderLoads.push_back(path);
            } else if (prefix.compare("texture") == 0) {
                std::string path;
                in >> path;
                this->textureLoads.push_back(path);
            } else if (prefix.compare("spritesheet") == 0) {
                std::string path;
                int cols, rows;

                in >> path;
                in >> cols;
                in >> rows;

                this->spritesheetLoads.push_back(std::make_tuple(path, cols, rows));
            } else if (prefix.compare("animation") == 0) {
                std::string name, path;
                float frameLength;
                bool loop;

                in >> name;
                in >> path;
                in >> frameLength;
                in >> loop;

                this->ssAnimationLoads.push_back(std::make_tuple(name, path, frameLength, loop));
            } else if (prefix.compare("font") == 0) {
                std::string path;
                int pnt;

                in >> path;
                in >> pnt;

                this->fontLoads.push_back(std::make_tuple(path, pnt));
            }
        }
    } catch (const std::exception& e) { throw std::string("Parse error."); }
}

// Loading an AssetLoads from a given location.
AssetLoads::AssetLoads(std::string path) throw(std::string) :
        AssetLoads(std::ifstream(path)) { }

// Filling an Assets given the local information.
void AssetLoads::fillAssets(Assets& assets) {
    for (auto& a: this->shaderLoads)
        assets.addShader(a);

    for (auto& a: this->textureLoads)
        assets.addTexture(a);

    for (auto& a: this->spritesheetLoads)
        assets.addSpritesheet(std::get<0>(a),
                              std::get<1>(a),
                              std::get<2>(a));

    for (auto& a: this->ssAnimationLoads)
        assets.addSSAnimation(std::get<0>(a),
                              assets.getSpritesheet(std::get<1>(a)),
                              std::get<2>(a),
                              std::get<3>(a));

    for (auto& a: this->fontLoads)
        assets.addFont(std::get<0>(a),
                       std::get<1>(a));
}
