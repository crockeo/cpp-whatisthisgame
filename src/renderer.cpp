#include "renderer.hpp"

//////////
// Code //

// Constructing a single render for a set of vertices, a Texture, and a
// sprite.
Render::Render(std::vector<std::tuple<float, float>> coords,
               std::vector<std::tuple<float, float>> texCoords,
               Texture texture, Shader shader, GLenum type) :
        texture(texture),
        shader(shader) {


    this->updateVertices(coords, texCoords);
}

// Cleaning up this render.
Render::~Render() {
    // TODO: FREEE FALLING
}

// Updating the set of vertices in this render.
void Render::updateVertices(std::vector<std::tuple<float, float>> coords,
                            std::vector<std::tuple<float, float>> texCoords) {
    // TODO: Should I throw an error from this?
    if (coords.size() != texCoords.size())
        return;

    // TODO: GET STUFF DONE.
}

// Binding this Render.
void Render::bind() const {
    // TODO: GET STUFF DONE.
}

// Unbinding this Render.
void Render::unbind() const {
    // TODO: GET STUFF DONE.
}

// Rendering this Render.
void Render::render() const {
    // TODO: GET STUFF DONE.
}

// Making the constructor private by default.
Renderer::Renderer() { }

// The destructor.
Renderer::~Renderer() { }

// The single, global reference.
Renderer* Renderer::renderer = nullptr;

// Getting the global instance of the renderer.
Renderer& Renderer::instance() {
    if (renderer == nullptr)
        renderer = new Renderer();
    return *renderer;
}

// Destroying the global renderer instance.
void Renderer::destroy() {
    if (renderer != nullptr)
        delete renderer;
    renderer = nullptr;
}
