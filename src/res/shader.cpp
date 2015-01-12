#include "shader.hpp"

//////////////
// Includes //
#include <iostream>
#include <fstream>

//////////
// Code //

// Attempting to create a specific shader.
GLuint loadShader(std::string path, GLenum type) {
    std::ifstream file(path);
    if (!file.good())
        return 0;

    std::string contents;
    while (!file.eof()) {
        if (file.peek() == -1)
            continue;
        contents.push_back((char)file.get());
    }

    GLuint shader = glCreateShader(type);
    if (shader == 0)
        return 0;

    const char* contentsCStr = contents.c_str();
    glShaderSource(shader, 1, &contentsCStr, nullptr);

    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        int len;
        GLchar log[1024];
        glGetShaderInfoLog(shader, 1024, &len, log);

        std::cout << "Failed to compile shader '" << path << "':" << std::endl;
        std::cout << log << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// The new copy constructor for this thingy.
Shader::Shader(const Shader& s) {
    this->id = s.id;
    this->original = false;
}

// Constructing a shader from a location on the disk.
Shader::Shader(std::string path) {
    this->original = false;

    GLuint vertShader = loadShader(path + ".vert", GL_VERTEX_SHADER);
    GLuint fragShader = loadShader(path + ".frag", GL_FRAGMENT_SHADER);
    GLuint geomShader = loadShader(path + ".geom", GL_GEOMETRY_SHADER);

    if (vertShader == 0 && fragShader == 0 && geomShader == 0) {
        this->id = 0;
        std::cout << "Failed to load any shaders for '" << path << "'." << std::endl;
    } else {
        this->id = glCreateProgram();

        if (vertShader != 0)
            glAttachShader(id, vertShader);
        if (fragShader != 0)
            glAttachShader(id, fragShader);
        if (geomShader != 0)
            glAttachShader(id, geomShader);

        glBindFragDataLocation(this->id, 0, "outColor");

        glLinkProgram(this->id);

        int linked;
        glGetProgramiv(this->id, GL_LINK_STATUS, &linked);
        if (linked == GL_FALSE) {
            std::cout << "Failed to link '" << path << "'!" << std::endl;
            glDeleteProgram(this->id);
        }

        this->original = true;

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        glDeleteShader(geomShader);
    }
}

// Deleting a shader.
Shader::~Shader() {
    if (this->original)
        glDeleteProgram(this->id);
}

// Accessing the shader id.
GLuint Shader::getID() const { return this->id; }
