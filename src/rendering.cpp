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

// The coordinates themselves for the rectangle.
std::vector<GLfloat> generateRectangle(float x, float y, float w, float h) {
    GLfloat vs[] = {
        x    , y    , 0.f, 0.f,
        x + w, y    , 1.f, 0.f,
        x + w, y + h, 1.f, 1.f,
        x    , y + h, 0.f, 1.f
    };

    std::vector<GLfloat> vertices;
    for (int i = 0; i < sizeof(vs) / sizeof(GLfloat); i++)
        vertices.push_back(vs[i]);

    return vertices;
}

// The order of vertices for a rectangle.
std::vector<GLuint> rectangleOrder() {
    GLuint os[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::vector<GLuint> order;
    for (int i = 0; i < sizeof(os) / sizeof(GLuint); i++)
        order.push_back(os[i]);

    return order;
}

// Constructing a new Render with a set of points, a texture, and a shader.
Render::Render(std::vector<GLfloat> vertices,
               std::vector<GLuint> order,
               GLenum type,
               Texture texture,
               Shader shader) :
        texture(texture),
        shader(shader) {
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);
    this->vertices = nullptr;
    this->order = nullptr;

    this->updateVertices(vertices, order, type);
}

// Constructing a new Render as a rectangle.
Render::Render(float x, float y,
               float w, float h,
               GLenum type,
               Texture texture,
               Shader shader) :
        Render(generateRectangle(x, y, w, h),
               rectangleOrder(),
               type,
               texture,
               shader) { }

// Destroying this render.
Render::~Render() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->ebo);

    if (this->vertices != nullptr)
        delete[] this->vertices;
    if (this->order != nullptr)
        delete[] this->order;
}

// Updating the set of vertices and order.
void Render::updateVertices(std::vector<GLfloat> vertices, std::vector<GLuint> order, GLenum type) {
    if (this->vertices != nullptr)
        delete[] this->vertices;
    if (this->order != nullptr)
        delete[] this->order;

    this->vertices = new GLfloat[vertices.size()];
    for (int i = 0; i < vertices.size(); i++)
        this->vertices[i] = vertices[i];

    this->order = new GLuint[order.size()];
    for (int i = 0; i < order.size(); i++)
        this->order[i] = order[i];

    this->points = order.size();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), this->vertices, type);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * order.size(), this->order, type);
}

// Performing this Render.
void Render::render(GLFWwindow* window) const {
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glUseProgram(this->shader.getID());

    // Setting the window size.
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glUniform2f(glGetUniformLocation(this->shader.getID(), "in_size"), width, height);

    // Setting the vertex coordinate.
    GLint posAttrib = glGetAttribLocation(this->shader.getID(), "in_vertexCoord");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    // Setting the texture coordinate.
    GLint texAttrib = glGetAttribLocation(this->shader.getID(), "in_texCoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    // Setting the texture sampler.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture.getID());
    glUniform1i(glGetUniformLocation(this->shader.getID(), "in_tex"), 0);

    glDrawElements(GL_TRIANGLES, this->points, GL_UNSIGNED_INT, 0);
}
