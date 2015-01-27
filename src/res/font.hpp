#ifndef _RES_FONT_HPP_
#define _RES_FONT_HPP_

//////////////
// Includes //
#include <drawtext.h>
#include <string>

//////////
// Code //

// A class to represent a font.
class Font {
private:
    struct dtx_font* font;
    bool original;
    int pnt;

    // Cleaning up this font.
    void destroy();

public:
    // Constructing a font from a location.
    Font(std::string, int);

    // Copy constructor.
    Font(const Font&);

    // Assignment operator.
    Font& operator=(const Font&);

    // Destroying this font.
    ~Font();

    // Binding this as the current font.
    void bind();
};

#endif
