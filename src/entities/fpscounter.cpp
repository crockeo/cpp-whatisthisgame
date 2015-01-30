#include "fpscounter.hpp"

//////////////
// Includes //
#include <sstream>

//////////
// Code //

// Starting the FPS counter.
FpsCounter::FpsCounter() :
        Entity(Rectangle(0, 0, 0, 0)) { }

// Updating.
void FpsCounter::update(GLFWwindow* window, const GameState& gs, float dt) {
    this->fps = 1 / dt;
}

// Initializing rendering.
void FpsCounter::initRender(GLFWwindow* window, const Assets& assets, Renders& renders) const {
    renders[0]["fps"] = new FontRender(
        assets.getShader("res/text"),
        assets.getFont("res/small-speculum.ttf")
    );
}

// Rendering shit.
void FpsCounter::render(GLFWwindow* window, Renders& renders) const {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    std::ostringstream str;
    str << "UPS: "
        << static_cast<int>(this->fps);

    renders[0]["fps"]->updateText(
        str.str(),
        width - 100, height - 20
    );
}
