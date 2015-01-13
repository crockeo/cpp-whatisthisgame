#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

//////////////
// Includes //
#include <vector>
#include <tuple>

#include "res/texture.hpp"
#include "res/shader.hpp"

//////////
// Code //

// A class to represent a single texture render.
class Render {
private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLfloat* vertices;
    Texture texture;
    Shader shader;

public:
    // Deleting the copy constructor.
    Render(const Render&) = delete;

    // Constructing a single render for a set of vertices, a Texture, and a
    // sprite.
    Render(std::vector<std::tuple<float, float>>, std::vector<std::tuple<float, float>>, Texture, Shader, GLenum);

    // Cleaning up this render.
    ~Render();

    // Updating the set of std::vector<std::tuple<float, float>> in this render.
    void updateVertices(std::vector<std::tuple<float, float>>, std::vector<std::tuple<float, float>>);

    // Binding this Render.
    void bind() const;

    // Unbinding this Render.
    void unbind() const;

    // Rendering this Render.
    void render() const;
};

// A class to encapsulate rendering.
class Renderer {
private:
    // Making the constructor private by default.
    Renderer();

    // The destructor.
    ~Renderer();

    // The single, global reference.
    static Renderer* renderer;

public:
    // Deleting the copy constructor.
    Renderer(const Renderer&) = delete;

    // Deleting the assignment operator.
    Renderer& operator=(const Renderer&) = delete;

    // Getting the global instance of the renderer.
    static Renderer& instance();

    // Destroying the global renderer instance.
    static void destroy();
};

#endif
