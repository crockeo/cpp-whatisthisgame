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

#endif
