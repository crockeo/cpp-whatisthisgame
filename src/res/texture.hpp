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
    int width, height;
    GLuint id;

public:
    // Loading a texture from a location on the disk.
    Texture(std::string);

    // Deleting this texture.
    ~Texture();

    // Accessing the texture id.
    GLuint getID() const;

    // Checking if the texture is good.
    bool good() const;

    // Getting the texture width and height respectively.
    int getWidth()  const;
    int getHeight() const;
};

#endif
