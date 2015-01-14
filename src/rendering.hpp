#ifndef _RENDERING_HPP_
#define _RENDERING_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>

#include "res/texture.hpp"
#include "res/shader.hpp"

//////////
// Code //

namespace rendering {
    // Generating a set of vertices for a rectangle.
    std::vector<std::tuple<float, float>> generateVertices(float, float, float, float);

    // Rendering a rectangle.
    void renderRectangle(GLFWwindow*, float, float, float, float, Texture, Shader);
}

// The coordinates themselves for the rectangle.
std::vector<GLfloat> generateRectangle(float, float, float, float);

// The order of vertices for a rectangle.
std::vector<GLuint> rectangleOrder();

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
    Render(float, float, float, float, GLenum, Texture, Shader);

    // Destroying this render.
    ~Render();

    // Updating the set of vertices and order.
    void updateVertices(std::vector<GLfloat>, std::vector<GLuint>, GLenum);

    // Performing this Render.
    void render(GLFWwindow*) const;
};

#endif
