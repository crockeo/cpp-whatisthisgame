#ifndef _RENDERING_HPP_
#define _RENDERING_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>

#include "res/texable.hpp"
#include "res/shader.hpp"
#include "rectangle.hpp"
#include "res/font.hpp"

//////////
// Code //

// The maximum number of layers.
const static float MAX_LAYERS = 24.f;

// The coordinates themselves for the rectangle.
std::vector<GLfloat> generateRectangle(Rectangle);

// The coordinates themselves for a set of rectangles.
std::vector<GLfloat> generateRectangles(std::vector<Rectangle>);

// The order of vertices for a rectangle.
std::vector<GLuint> rectangleOrder();

// The order for multiple rectangles.
std::vector<GLuint> rectangleOrders(int);

// An abstract class to represent that something is renderable.
class Renderable {
public:
    virtual void render(GLFWwindow*) const = 0;

    virtual void updateVertices(std::vector<GLfloat>, std::vector<GLuint>, GLenum) { }
    virtual void updateText(std::string, float, float) { }
};

// A class to represent a single render.
class Render : public Renderable {
private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    const Texable& texture;
    const Shader& shader;

    GLfloat* vertices;
    GLuint* order;
    int points;

public:
    // Deleting the copy constructor!
    Render(const Render&) = delete;

    // Constructing a new Render with a set of points, a texture, and a shader.
    Render(std::vector<GLfloat>, std::vector<GLuint>, GLenum, const Texable&, const Shader&);

    // Constructing a new Render as a rectangle.
    Render(Rectangle, GLenum, const Texable&, const Shader&);

    // Destroying this render.
    ~Render();

    // Updating the set of vertices and order.
    void updateVertices(std::vector<GLfloat>, std::vector<GLuint>, GLenum);

    // Performing this Render.
    void render(GLFWwindow*) const;
};

// A specific type of render for rendering a font.
class FontRender : public Renderable {
private:
    std::string text;
    Shader shader;
    float x, y;
    Font font;

public:
    // Creating a FontRender with a given font, a given string, and the position
    // to render.
    FontRender(Shader, Font, std::string, float, float);

    // Creating a FontRender from a font, but without a string.
    FontRender(Shader, Font);

    // Rendering this FontRender.
    void render(GLFWwindow*) const;

    // Updating the FontRender.
    void updateText(std::string, float, float);
};

// A set of Renders to perform on every tick.
class Renders {
private:
    std::vector<std::unordered_map<std::string, Renderable*>*> renders;

public:
    // Keeping the Renders from being copied or set.
    Renders(const Renders&) = delete;
    Renders& operator=(const Renders&) = delete;

    // Constructing a set of renders with a given size.
    Renders(int);

    // Destroying the set of renders.
    ~Renders();
    
    // Getting a specific map.
    std::unordered_map<std::string, Renderable*>& operator[](int);

    // Rendering this Renders.
    void renderAll(GLFWwindow*) const;
};

// A type to define a set of Renders.
//typedef std::unordered_map<std::string, Render*> Renders;

#endif
