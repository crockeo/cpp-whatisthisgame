#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <string>
#include <vector>

#include "res/animation.hpp"
#include "res/texture.hpp"
#include "res/shader.hpp"
#include "timer.hpp"

//////////
// Code //

// A class to encapsulate asset loading and referencing.
class Assets {
private:
    std::unordered_map<std::string, Animation*> animations;
    std::unordered_map<std::string, Texture*> textures;
    std::unordered_map<std::string, Shader*> shaders;

public:
    // Removing the implicit copy constructor.
    Assets(const Assets&) = delete;

    // Creating an empty set of assets.
    Assets();

    // Destructing assets.
    ~Assets();

    // Adding different kinds of assets.
    void addAnimation(std::string, std::vector<Texture>, float, bool);
    void addAnimation(std::string, std::vector<Texture>, float);
    void addTexture(std::string);
    void addShader(std::string);

    // Getting the vector of animation timers.
    std::vector<Timer*> getAnimationTimers() const;

    // Getting different kind of assets.
    Animation getAnimation(std::string) const;
    Texture getTexture(std::string) const;
    Shader getShader(std::string) const;
};

// Loading the default set of assets into the ref.
void loadAssets(Assets&);

#endif
