#pragma once

#include "glfwpp/window.hpp"

#include "theia/hermes.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

namespace glfwpp {
namespace event {
struct KeyEvent {
    MAKE_HERMES_ID(glfwpp::event::KeyEvent);
    Window window;
    int key;
    int scancode;
    int action;
    int mods;
};

struct CharEvent {
    MAKE_HERMES_ID(glfwpp::event::CharEvent);
    Window window;
    unsigned int codepoint;
};

struct CursorPosEvent {
    MAKE_HERMES_ID(glfwpp::event::CursorPosEvent);
    Window window;
    double xpos;
    double ypos;
};

struct CursorEnterEvent {
    MAKE_HERMES_ID(glfwpp::event::CursorEnterEvent);
    Window window;
    bool entered;
};

struct MouseButtonEvent {
    MAKE_HERMES_ID(glfwpp::event::MouseButtonEvent);
    Window window;
    int button;
    int action;
    int mods;
};

struct ScrollEvent {
    MAKE_HERMES_ID(glfwpp::event::ScrollEvent);
    Window window;
    double xoffset;
    double yoffset;
};

struct DropEvent {
    MAKE_HERMES_ID(glfwpp::event::DropEvent);
    Window window;
    int count;
    const char **paths;
};
} // namespace event

void set_input_callbacks(Window &window);

bool supports_raw_mouse_motion();

void set_clipboard_string(const std::string &s);

namespace event {
enum class JoystickEventType {
    Connected = GLFW_CONNECTED,
    Disconnected = GLFW_DISCONNECTED,
};

struct JoystickEvent {
    MAKE_HERMES_ID(glfwpp::event::JoystickEvent);
    int jid;
    JoystickEventType event;
};
} // namespace event

// TODO: Joystick stuff
} // namespace glfwpp