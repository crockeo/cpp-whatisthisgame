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

    glfwMakeContextCurrent(window);
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glColor3f(1.f, 0.3f, 0.6f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.5f,  0.5f);
            glVertex2f(-0.5f,  0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
