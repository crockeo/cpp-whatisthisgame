#ifndef _RENDERING_HPP_
#define _RENDERING_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>

#include "res/texture.hpp"
#include "res/shader.hpp"
#include "rectangle.hpp"

//////////
// Code //

// The coordinates themselves for the rectangle.
std::vector<GLfloat> generateRectangle(Rectangle);

// The coordinates themselves for a set of rectangles.
std::vector<GLfloat> generateRectangles(std::vector<Rectangle>);

// The order of vertices for a rectangle.
std::vector<GLuint> rectangleOrder();

// The order for multiple rectangles.
std::vector<GLuint> rectangleOrders(int);

// A class to represent a single render.
class Render {
private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    Texture texture;
    Shader shader;

    GLfloat* vertices;
    GLuint* order;
    int points;

public:
    // Deleting the copy constructor!
    Render(const Render&) = delete;

    // Constructing a new Render with a set of points, a texture, and a shader.
    Render(std::vector<GLfloat>, std::vector<GLuint>, GLenum, Texture, Shader);

    // Constructing a new Render as a rectangle.
    Render(Rectangle, GLenum, Texture, Shader);

    // Destroying this render.
    ~Render();

    // Updating the set of vertices and order.
    void updateVertices(std::vector<GLfloat>, std::vector<GLuint>, GLenum);

    // Performing this Render.
    void render(GLFWwindow*) const;
};

// A type to define a set of Renders.
typedef std::unordered_map<std::string, Render*> Renders;

// Rendering every single Render within a Renders.
void renderAll(GLFWwindow*, const Renders&);

#endif
