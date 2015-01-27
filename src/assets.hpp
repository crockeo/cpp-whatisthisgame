#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <istream>
#include <memory>
#include <string>
#include <vector>

#include "res/spritesheet.hpp"
#include "res/ssanimation.hpp"
#include "res/animation.hpp"
#include "res/texture.hpp"
#include "res/shader.hpp"
#include "res/font.hpp"
#include "timer.hpp"

//////////
// Code //

// A class to encapsulate asset loading and referencing.
class Assets {
private:
    std::unordered_map<std::string, std::unique_ptr<Spritesheet>> spritesheets;
    std::unordered_map<std::string, std::unique_ptr<SSAnimation>> ssAnimations;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<Font>> fonts;

public:
    // Removing the implicit copy constructor.
    Assets(const Assets&) = delete;

    // Creating an empty set of assets.
    Assets();

    // Adding different kinds of assets.
    void addSpritesheet(std::string, int, int);
    void addSSAnimation(std::string, Spritesheet, float, bool);
    void addSSAnimation(std::string, Spritesheet, float);
    void addAnimation(std::string, std::vector<Texture>, float, bool);
    void addAnimation(std::string, std::vector<Texture>, float);
    void addTexture(std::string);
    void addShader(std::string);
    void addFont(std::string, int);

    // Getting the vector of animation timers.
    std::vector<std::shared_ptr<Timer>> getAnimationTimers() const;

    // Getting different kind of assets.
    const Spritesheet& getSpritesheet(std::string) const;
    const SSAnimation& getSSAnimation(std::string) const;
    const Animation& getAnimation(std::string) const;
    const Texture& getTexture(std::string) const;
    const Shader& getShader(std::string) const;
    const Font& getFont(std::string) const;
};

// The set of Assets to load.
class AssetLoads {
private:
    std::vector<std::tuple<std::string, int, int>> spritesheetLoads;
    std::vector<std::tuple<std::string, std::string, float, bool>> ssAnimationLoads;
    std::vector<std::tuple<std::string, int>> fontLoads;
    std::vector<std::string> textureLoads;
    std::vector<std::string> shaderLoads;

public:
    // Loading an AssetLoads from an istream.
    AssetLoads(std::istream&&) throw(std::string);

    // Loading an AssetLoads from a given location.
    AssetLoads(std::string) throw(std::string);

    // Filling an Assets given the local information.
    void fillAssets(Assets&);
};

#endif
