//////////////
// Includes //
#include <GLFW/glfw3.h>
#include <iostream>

//////////
// Code //

// The entry point to the application.
int main() {
    if (!glfwInit()) {
        std::cout << "Could not start GLFW." << std::endl;
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello world", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Could not open the GLFW window." << std::endl;
        glfwTerminate();
        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
