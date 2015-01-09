#include "shader.hpp"

//////////
// Code //

// Constructing a shader from a location on the disk.
Shader::Shader(std::string path) { }

// Deleting a shader.
Shader::~Shader() { }

// Accessing the shader id.
GLuint Shader::getID() const { return this->id; }
