#include "renderer.hpp"

//////////
// Code //

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
