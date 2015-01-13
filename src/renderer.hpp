#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

//////////////
// Includes //
#include <vector>

//////////
// Code //


// A class to encapsulate rendering.
class Renderer {
private:
    // Making the constructor private by default.
    Renderer();

    // The destructor.
    ~Renderer();

    // The single, global reference.
    static Renderer* renderer;

public:
    // Deleting the copy constructor.
    Renderer(const Renderer&) = delete;

    // Deleting the assignment operator.
    Renderer& operator=(const Renderer&) = delete;

    // Getting the global instance of the renderer.
    static Renderer& instance();

    // Destroying the global renderer instance.
    static void destroy();
};

#endif
