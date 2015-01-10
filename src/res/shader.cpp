#include "shader.hpp"

//////////////
// Includes //
#include <fstream>

//////////
// Code //

// Attempting to create a specific shader.
GLuint loadShader(std::string path, GLenum type) {
    std::ifstream file(path);
    if (!file.good())
        return 0;

    std::string contents;
    while (!file.eof())
        contents.push_back((char)file.get());

    GLuint shader = glCreateShader(type);
    if (shader == 0)
        return 0;

    const char* contentsCStr = contents.c_str();
    glShaderSource(shader, 1, &contentsCStr, nullptr);

    glCompileShader(shader);

    return shader;
}

// Constructing a shader from a location on the disk.
Shader::Shader(std::string path) {
    GLuint vertShader = loadShader(path + ".vert", GL_VERTEX_SHADER);
    GLuint fragShader = loadShader(path + ".frag", GL_FRAGMENT_SHADER);
    GLuint geomShader = loadShader(path + ".geom", GL_GEOMETRY_SHADER);

    GLuint id = glCreateProgram();

    if (vertShader != 0)
        glAttachShader(id, vertShader);
    if (fragShader != 0)
        glAttachShader(id, fragShader);
    if (geomShader != 0)
        glAttachShader(id, geomShader);

    glLinkProgram(id);
}

// Deleting a shader.
Shader::~Shader() { }

// Accessing the shader id.
GLuint Shader::getID() const { return this->id; }
