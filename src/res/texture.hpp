#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

//////////////
// Includes //
#include <GLFW/glfw3.h>
#include <string>

//////////
// Code //

// A class to represent a texture.
class Texture {
private:
    GLuint id;

public:
    // Removing the copy constructor.
    Texture(const Texture&) = delete;

    // Loading a texture from a location on the disk.
    Texture(std::string);

    // Deleting this texture.
    ~Texture();

    // Binding this texture for rendering.
    void bind() const;

    // Unbinding a texture.
    void unbind() const;
};

#endif
