#ifndef _SHADER_HPP_
#define _SHADER_HPP_

//////////////
// Includes //
#include <GLFW/glfw3.h>
#include <string>

//////////
// Code //

// A class to represent an OpenGL shader.
class Shader {
private:
    GLuint id;    

public:
    // Deleting the copy constructor.
    Shader(const Shader&) = delete;

    // Constructing a shader from a location on the disk.
    Shader(std::string);

    // Deleting a shader.
    ~Shader();

    // Accessing the shader id.
    GLuint getID() const;
};

#endif
