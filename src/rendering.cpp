#include "rendering.hpp"

//////////
// Code //

// Generating a set of vertices for a rectangle.
std::vector<std::tuple<float, float>> rendering::generateVertices(float x, float y, float w, float h) {
    std::vector<std::tuple<float, float>> points;

    points.push_back(std::make_tuple(x    , y    ));
    points.push_back(std::make_tuple(x    , y + h));
    points.push_back(std::make_tuple(x + w, y + h));
    points.push_back(std::make_tuple(x    , y    ));
    points.push_back(std::make_tuple(x + w, y + h));
    points.push_back(std::make_tuple(x + w, y    ));

    return points;
}

// Rendering a set of vertices.
void rendering::renderVertices(std::vector<std::tuple<float, float>> vertices, Texture t, Shader s) {
    float* fs = new float[vertices.size() * 2];

    int vi = 0, fi = 0;
    while (vi < vertices.size() && fi < vertices.size() * 2) {
        fs[fi    ] = std::get<0>(vertices[vi]);
        fs[fi + 1] = std::get<1>(vertices[vi]);

        vi += 1;
        fi += 2;
    }

    // Setting up the VBO.
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fs), fs, GL_STATIC_DRAW);

    // Setting up the VAO.
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

    // TODO: Do some rendering.

    // Cleaning up the VBO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Cleaning up the VAO.
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    // Deleting the fs thing.
    delete[] fs;
}

// Rendering a rectangle.
void rendering::renderRectangle(float x, float y, float w, float h, Texture t, Shader s) {
    rendering::renderVertices(rendering::generateVertices(x, y, w, h), t, s);
}
