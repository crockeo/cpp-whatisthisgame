#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include "res/spritesheet.hpp"
#include "res/ssanimation.hpp"
#include "res/animation.hpp"
#include "res/texture.hpp"
#include "res/shader.hpp"
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

    // Getting the vector of animation timers.
    std::vector<std::shared_ptr<Timer>> getAnimationTimers() const;

    // Getting different kind of assets.
    const Spritesheet& getSpritesheet(std::string) const;
    const SSAnimation& getSSAnimation(std::string) const;
    const Animation& getAnimation(std::string) const;
    const Texture& getTexture(std::string) const;
    const Shader& getShader(std::string) const;
};

// Loading the default set of assets into the ref.
void loadAssets(Assets&);

#endif
