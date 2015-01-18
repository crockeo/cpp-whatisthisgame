#ifndef _RES_TEXABLE_HPP_
#define _RES_TEXABLE_HPP_

//////////////
// Includes //
#include <GL/glew.h>

//////////
// Code //

// A class to act as an interface for an object that can have a texture ID.
class Texable {
public:
    // Getting the texture ID.
    virtual GLuint getID() const { return 0; }
};

#endif
