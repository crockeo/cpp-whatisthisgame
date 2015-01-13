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

// Rendering a rectangle.
void rendering::renderRectangle(GLFWwindow* window, float x, float y, float w, float h, Texture t, Shader s) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {
        x    , y    , 0.f, 0.f,
        x + w, y    , 1.f, 0.f,
        x + w, y + h, 1.f, 1.f,
        x    , y + h, 0.f, 1.f
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

    // Setting the window size.
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glUniform2f(glGetUniformLocation(s.getID(), "in_size"), width, height);

    // Setting the vertex coordinate.
    GLint posAttrib = glGetAttribLocation(s.getID(), "in_vertexCoord");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    // Setting the texture coordinate.
    GLint texAttrib = glGetAttribLocation(s.getID(), "in_texCoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    // Setting the texture sampler.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t.getID());
    glUniform1i(glGetUniformLocation(s.getID(), "in_tex"), 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}
