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

// Binding this texture for rendering.
void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->id);
}

// Unbinding a texture.
void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
