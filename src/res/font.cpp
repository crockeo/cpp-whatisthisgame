#include "font.hpp"

//////////
// Code //

// Cleaning up this font.
void Font::destroy() {
    if (this->original)
        return;
}

// Constructing a font from a location.
Font::Font(std::string path, int pnt) {
    this->font     = dtx_open_font(path.c_str(), pnt);
    this->original = true;
    this->pnt      = pnt;
}

// Copy constructor.
Font::Font(const Font& font) {
    this->font     = font.font;
    this->original = false;
    this->pnt      = font.pnt;
}

// Assignment operator.
Font& Font::operator=(const Font& font) {
    this->destroy();

    this->font     = font.font;
    this->original = false;
    this->pnt      = font.pnt;

    return *this;
}

// Destroying this font.
Font::~Font() {
    this->destroy();
}

// Binding this as the current font.
void Font::bind() {
    // TODO: How do bind font?
}
