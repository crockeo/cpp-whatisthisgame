#include "background.hpp"

//////////
// Code //

// Updating the size of the background.
void Background::updateSize(GLFWwindow* window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    this->position().w = width;
    this->position().h = height;
}

// Creating a new background from GLFWwindow.
Background::Background() :
        Entity(Rectangle(0, 0, 0, 0)) { }

// Updating this entity.
void Background::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->updateSize(window);
}

// Providing the initial render for this entity.
void Background::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[2]["background"] = new Render(this->getPosition(),
                                          GL_DYNAMIC_DRAW,
                                          assets.getTexture("res/background.png"),
                                          assets.getShader("res/game2d"));
}

// Rendering this entity.
void Background::render(GLFWwindow* window, Renders& renders) const {
    renders[2]["background"]->updateVertices(generateRectangle(this->getPosition()),
                                             rectangleOrder(),
                                             GL_DYNAMIC_DRAW);
}
