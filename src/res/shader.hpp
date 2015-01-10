#ifndef _SHADER_HPP_
#define _SHADER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <string>

//////////
// Code //

// A class to represent an OpenGL shader.
class Shader {
private:
    GLuint id;    

public:
    // Constructing a shader from a location on the disk.
    Shader(std::string);

    // Deleting a shader.
    ~Shader();

    // Accessing the shader id.
    GLuint getID() const;
};

#endif
