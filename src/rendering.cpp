#include "rendering.hpp"

#include <iostream>

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
void rendering::renderVertices(std::vector<std::tuple<float, float>> vs, Texture t, Shader s) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    GLfloat vertices[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glUseProgram(s.getID());
    GLint posAttrib = glGetAttribLocation(s.getID(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(s.getID(), "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    GLint texAttrib = glGetAttribLocation(s.getID(), "texCoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t.getID());
    glUniform1i(glGetUniformLocation(s.getID(), "texSampler"), 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

// Rendering a rectangle.
void rendering::renderRectangle(float x, float y, float w, float h, Texture t, Shader s) {
    rendering::renderVertices(rendering::generateVertices(x, y, w, h), t, s);
}
