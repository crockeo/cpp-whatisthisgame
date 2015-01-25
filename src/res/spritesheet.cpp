#include "spritesheet.hpp"

//////////
// Code //

// Constructing a Spritesheet from a given texture and its number of rows /
// columns.
Spritesheet::Spritesheet(Texture tex, int cols, int rows) :
        tex(tex) {
    this->cols = cols;
    this->rows = rows;

    this->col = 1;
    this->row = 1;
}

// Accessing specific columns or rows of the Spritesheet.
int Spritesheet::getCols() const { return this->cols; }
int Spritesheet::getRows() const { return this->rows; }

// Getting the size of the Spritesheet.
std::tuple<int, int> Spritesheet::getSize() const {
    return std::make_tuple(this->cols, this->rows);
}

// Setting the current position of the Spritesheet.
void Spritesheet::setPosition(int col, int row) {
    this->col = col + 1;
    this->row = row + 1;
}

// Getting the current position of the Spritesheet.
std::tuple<int, int> Spritesheet::getPosition() const {
    return std::make_tuple(this->col, this->row);
}

// Getting the texture coordinates to use pretending that the spritesheet is
// at a given location.
std::vector<GLfloat> Spritesheet::getTextureCoordsAt(int col, int row) const {
    float x = col / static_cast<float>(this->cols),
          y = row / static_cast<float>(this->rows),
          w = 1   / static_cast<float>(this->cols),
          h = 1   / static_cast<float>(this->rows);


    std::vector<GLfloat> tc {
        x    , y    ,
        x + w, y    ,
        x + w, y + h,
        x    , y + h
    };
    
    return tc;
}

// Getting the ID of the texture.
GLuint Spritesheet::getID() const { return this->tex.getID(); }

// Getting the texture coordinates to use.
std::vector<GLfloat> Spritesheet::getTextureCoords() const {
    return this->getTextureCoordsAt(this->col, this->row);
}
