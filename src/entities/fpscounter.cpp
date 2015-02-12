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
    if (dt == 0)
        return;

    if (this->fpses.size() < FpsCounter::averageLength)
        this->fpses.push_back(1 / dt);
    else {
        for (int i = this->fpses.size() - 1; i > 0; i--)
            this->fpses[i] = this->fpses[i - 1];
        this->fpses[0] = 1 / dt;
    }

    this->fps = 0;
    for (float f: this->fpses)
        this->fps += f;
    this->fps /= this->fpses.size();
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
