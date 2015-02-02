#include "font.hpp"

//////////////
// Includes //
#include <iostream>

//////////
// Code //

FT_Library* FontLib::ft = nullptr;

// Getting an instance of the FT_Library.
FT_Library FontLib::instance() {
   if (FontLib::ft == nullptr) {
        ft = new FT_Library;
        FT_Init_FreeType(ft);
   }

   return *ft;
}

// Cleaning up this font.
void Font::destroy() {
    if (this->original)
        return;
}

// Constructing a font from a location.
Font::Font(std::string path, int pnt) {
    if (FT_New_Face(FontLib::instance(), path.c_str(), 0, &this->fontFace)) {
        std::cout << "Failed to load font '" << path << "'!" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(this->fontFace, 0, pnt);

    this->original = true;
    this->pnt      = pnt;
}

// Copy constructor.
Font::Font(const Font& font) {
    this->fontFace = font.fontFace;
    this->original = false;
    this->pnt      = font.pnt;
}

// Assignment operator.
Font& Font::operator=(const Font& font) {
    this->destroy();

    this->fontFace = font.fontFace;
    this->original = false;
    this->pnt      = font.pnt;

    return *this;
}

// Destroying this fontFace.
Font::~Font() { this->destroy(); }

// Finding the display width of a string.
float Font::displayWidth(std::string str) const {
    float x = 0;
    const char* ptr;
    for (ptr = str.c_str(); *ptr; ptr++) {
        if (FT_Load_Char(this->fontFace, *ptr, FT_LOAD_RENDER))
            continue;
        x += (this->fontFace->glyph->advance.x >> 6);
    }

    return x;
}

// Finding the display height of a string.
float Font::displayHeight(std::string) const {
    return this->pnt;
}

// Drawing text 'n' stuff.
void Font::drawText(GLFWwindow* window, Shader shader, const char* str,
                    float x, float y) const {
    const char* ptr;

    glUseProgram(shader.getID());

    // Getting the window size.
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glUniform2f(glGetUniformLocation(shader.getID(), "in_size"), width, height);

    // Setting the text color.
    glUniform4f(glGetUniformLocation(shader.getID(), "in_color"), 1, 1, 1, 1);

    // Loading up the texture.
    GLuint tex;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(glGetUniformLocation(shader.getID(), "in_tex"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Loading up the VBO.
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Loading up the EBO.
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    GLuint order[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(order), order, GL_STATIC_DRAW);

    // Setting the vertex coordinate.
    GLint posAttrib = glGetAttribLocation(shader.getID(), "in_coords");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    FT_GlyphSlot g = this->fontFace->glyph;
    for (ptr = str; *ptr; ptr++) {
        if (FT_Load_Char(this->fontFace, *ptr, FT_LOAD_RENDER))
            continue;

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            g->bitmap.width,
            g->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            g->bitmap.buffer
        );

        float w = g->bitmap.width,
              h = g->bitmap.rows ;

        GLfloat box[] = {
            x    , y    , 0, 1,
            x + w, y    , 1, 1,
            x + w, y + h, 1, 0,
            x    , y + h, 0, 0
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
        glDrawElements(GL_TRIANGLES, sizeof(order), GL_UNSIGNED_INT, 0);

        x += g->advance.x >> 6;
        y += g->advance.y >> 6;
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteTextures(1, &tex);
}
