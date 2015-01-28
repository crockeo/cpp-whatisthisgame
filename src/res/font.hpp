#ifndef _RES_FONT_HPP_
#define _RES_FONT_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

#include "shader.hpp"

//////////
// Code //

class FontLib {
private:
    static FT_Library* ft;

public:
    // Getting an instance of the FT_Library.
    static FT_Library instance();
};

// A class to represent a font.
class Font {
private:
    FT_Face fontFace;
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

    // Drawing text 'n' stuff.
    void drawText(GLFWwindow*, Shader, const char*,
                  float, float) const;
};

#endif