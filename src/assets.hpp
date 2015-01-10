#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <string>

#include "res/texture.hpp"
#include "res/shader.hpp"

//////////
// Code //

// 
class Assets {
private:
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
    void addTexture(std::string);
    void addShader(std::string);

    // Getting different kind of assets.
    Texture getTexture(std::string) const;
    Shader getShader(std::string) const;
};

#endif
