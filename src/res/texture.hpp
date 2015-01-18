#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <string>

#include "texable.hpp"

//////////
// Code //

// A class to represent a texture.
class Texture : public Texable {
private:
    int width, height;
    bool original;
    GLuint id;

public:
    // The new copy constructor for this thingy.
    Texture(const Texture&);

    // Loading a texture from a location on the disk.
    Texture(std::string);

    // Deleting this texture.
    ~Texture();

    // Accessing the texture id.
    GLuint getID() const override;

    // Checking if the texture is good.
    bool good() const;

    // Getting the texture width and height respectively.
    int getWidth()  const;
    int getHeight() const;
};

#endif
