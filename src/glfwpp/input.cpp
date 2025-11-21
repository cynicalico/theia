#include "glfwpp/input.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void glfwpp::set_input_callbacks(GLFWwindow *window) {
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        theia::Hermes::instance().publish<event::KeyE>(window, key, scancode, action, mods);
    });

    glfwSetCharCallback(window, [](GLFWwindow *window, unsigned int codepoint) {
        theia::Hermes::instance().publish<event::CharE>(window, codepoint);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos) {
        theia::Hermes::instance().publish<event::CursorPosE>(window, xpos, ypos);
    });

    glfwSetCursorEnterCallback(window, [](GLFWwindow *window, int entered) {
        theia::Hermes::instance().publish<event::CursorEnterE>(window, entered == GLFW_TRUE);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
        theia::Hermes::instance().publish<event::MouseButtonE>(window, button, action, mods);
    });

    glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset) {
        theia::Hermes::instance().publish<event::ScrollE>(window, xoffset, yoffset);
    });

    glfwSetJoystickCallback(
        [](int joy, int event) { theia::Hermes::instance().publish<event::JoystickE>(joy, event); });

    glfwSetDropCallback(window, [](GLFWwindow *window, int count, const char **paths) {
        theia::Hermes::instance().publish<event::DropE>(window, count, paths);
    });
}
