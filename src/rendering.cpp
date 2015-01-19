#include "rendering.hpp"

//////////
// Code //

template <class T>
std::vector<T> flatten(std::vector<std::vector<T>> levels) {
    std::vector<T> ret;

    for (auto a = levels.begin(); a != levels.end(); a++)
        for (auto b = a->begin(); b != a->end(); b++)
            ret.push_back(*b);

    return ret;
}

// The coordinates themselves for the rectangle.
std::vector<GLfloat> generateRectangle(Rectangle r) {
    std::vector<GLfloat> vertices {
        r.x      , r.y      , 0.f, 0.f,
        r.x + r.w, r.y      , 1.f, 0.f,
        r.x + r.w, r.y + r.h, 1.f, 1.f,
        r.x      , r.y + r.h, 0.f, 1.f
    };

    return vertices;
}

// The coordinates themselves for a set of rectangles.
std::vector<GLfloat> generateRectangles(std::vector<Rectangle> rs) {
    std::vector<std::vector<GLfloat>> vs;
    for (auto it = rs.begin(); it != rs.end(); it++)
        vs.push_back(generateRectangle(*it));
    return flatten(vs);
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

// The order for multiple rectangles.
std::vector<GLuint> rectangleOrders(int num) {
    if (num <= 0)
        return std::vector<GLuint>();

    std::vector<GLuint> os;
    for (int i = 0; i < num; i++) {
        std::vector<GLuint> order = rectangleOrder();
        for (auto it = order.begin(); it != order.end(); it++)
            os.push_back(*it + 4 * i);
    }

    return os;
}

// Constructing a new Render with a set of points, a texture, and a shader.
Render::Render(std::vector<GLfloat> vertices,
               std::vector<GLuint> order,
               GLenum type,
               const Texable& texture,
               const Shader& shader) :
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
Render::Render(Rectangle r,
               GLenum type,
               const Texable& texture,
               const Shader& shader) :
        Render(generateRectangle(r),
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

// Constructing a set of renders with a given size.
Renders::Renders(int size) {
    for (int i = 0; i < size; i++)
        this->renders.push_back(new std::unordered_map<std::string, Render*>());
}

// Destroying the set of renders.
Renders::~Renders() {
    // TODO: Remove.
}

// Getting a specific map.
std::unordered_map<std::string, Render*>& Renders::operator[](int i) {
    return *this->renders[i];
}

// Rendering this Renders.
void Renders::renderAll(GLFWwindow* window) const {
    for (int i = this->renders.size() - 1; i >= 0; i--) {
        std::unordered_map<std::string, Render*>* r = this->renders[i];

        for (auto it = r->begin(); it != r->end(); it++)
            std::get<1>(*it)->render(window);
    }
}
