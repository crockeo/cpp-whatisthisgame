#include "spritesheet.hpp"

//////////
// Code //

// Constructing a Spritesheet from a given texture and its number of rows /
// columns.
Spritesheet::Spritesheet(Texture tex, int cols, int rows) :
        tex(tex) {
    this->cols = cols;
    this->rows = rows;

    this->col = 0;
    this->row = 0;
}

// Getting the size of the Spritesheet.
std::tuple<int, int> Spritesheet::getSize() const {
    return std::make_tuple(this->cols, this->rows);
}

// Setting the current position of the Spritesheet.
void Spritesheet::setPosition(int col, int row) {
    this->col = col;
    this->row = row;
}

// Getting the current position of the Spritesheet.
std::tuple<int, int> Spritesheet::getPosition() const {
    return std::make_tuple(this->col, this->row);
}

// Getting the ID of the texture.
GLuint Spritesheet::getID() const { return this->tex.getID(); }

// Getting the texture coordinates to use.
std::vector<GLfloat> Spritesheet::getTextureCoords() const {
    float icol = this->col / static_cast<float>(this->cols),
          irow = this->row / static_cast<float>(this->rows);

    std::vector<GLfloat> tc {
        icol * this->col       , irow * this->row       ,
        icol * this->col + icol, irow * this->row       ,
        icol * this->col + icol, irow * this->row + irow,
        icol * this->col       , irow * this->row + irow
    };
    
    return tc;
}
