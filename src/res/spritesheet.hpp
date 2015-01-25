#ifndef _RES_SPRITESHEET_HPP_
#define _RES_SPRITESHEET_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <tuple>

#include "texable.hpp"
#include "texture.hpp"

//////////
// Code //

// A type to represent a sheet of sprites.
class Spritesheet : public Texable {
private:
    int cols, rows;
    int col, row;
    Texture tex;

public:
    // Constructing a Spritesheet from a given texture and its number of rows /
    // columns.
    Spritesheet(Texture, int, int);

    // Accessing specific columns or rows of the Spritesheet.
    int getCols() const;
    int getRows() const;

    // Getting the size of the Spritesheet.
    std::tuple<int, int> getSize() const;

    // Setting the current position of the Spritesheet.
    void setPosition(int, int);

    // Getting the current position of the Spritesheet.
    std::tuple<int, int> getPosition() const;

    // Getting the texture coordinates to use pretending that the spritesheet is
    // at a given location.
    std::vector<GLfloat> getTextureCoordsAt(int, int) const;

    // Getting the ID of the texture.
    GLuint getID() const override;

    // Getting the texture coordinates to use.
    std::vector<GLfloat> getTextureCoords() const override;
};

#endif
