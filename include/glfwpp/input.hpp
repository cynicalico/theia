#pragma once

#include "theia/hermes.hpp"

#include <string>

struct GLFWwindow;

namespace glfwpp {
namespace event {
struct KeyE {
    MAKE_HERMES_ID(glfwpp::KeyE);
    GLFWwindow *window;
    int key;
    int scancode;
    int action;
    int mods;
};

struct CharE {
    MAKE_HERMES_ID(glfwpp::CharE);
    GLFWwindow *window;
    unsigned int codepoint;
};

struct CursorPosE {
    MAKE_HERMES_ID(glfwpp::CursorPosE);
    GLFWwindow *window;
    double xpos;
    double ypos;
};

struct CursorEnterE {
    MAKE_HERMES_ID(glfwpp::CursorEnterE);
    GLFWwindow *window;
    bool entered;
};

struct MouseButtonE {
    MAKE_HERMES_ID(glfwpp::MouseButtonE);
    GLFWwindow *window;
    int button;
    int action;
    int mods;
};

struct ScrollE {
    MAKE_HERMES_ID(glfwpp::ScrollE);
    GLFWwindow *window;
    double xoffset;
    double yoffset;
};

struct JoystickE {
    MAKE_HERMES_ID(glfwpp::JoystickE);
    int jid;
    int event;
};

struct DropE {
    MAKE_HERMES_ID(glfwpp::DropE);
    GLFWwindow *window;
    int count;
    const char **paths;
};
} // namespace event

void set_input_callbacks(GLFWwindow *window);

bool supports_raw_mouse_motion();

void set_clipboard_string(const std::string &s);
} // namespace glfwpp