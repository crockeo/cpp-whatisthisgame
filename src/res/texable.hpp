#ifndef _RES_TEXABLE_HPP_
#define _RES_TEXABLE_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <vector>

//////////
// Code //

// A class to act as an interface for an object that can have a texture ID.
class Texable {
public:
    // Getting the texture ID.
    virtual GLuint getID() const = 0;

    // Getting the texture coordinates.
    virtual std::vector<GLfloat> getTextureCoords() const = 0;
};

#endif
