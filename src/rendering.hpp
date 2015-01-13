#ifndef _RENDERING_HPP_
#define _RENDERING_HPP_

//////////////
// Includes //
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
    void renderRectangle(float, float, float, float, Texture, Shader);
}

#endif
