#include "texture.hpp"

//////////
// Code //

// Loading a texture from a location on the disk.
Texture::Texture(std::string path) {
    // TODO: Find out how to load a texture.
}

// Deleting this texture.
Texture::~Texture() {
   glDeleteTextures(1, &this->id);
}

// Accessing the texture id.
GLuint Texture::getID() const { return this->id; }
