#include "glfwpp/input.hpp"
#include "theia/dear.hpp"

void glfwpp::set_input_callbacks(Window &window) {
    window.set_key_callback([](GLFWwindow *window_, int key, int scancode, int action, int mods) {
        theia::Dear::instance().key_callback(window_, key, scancode, action, mods);
        if (theia::Dear::instance().want_capture_keyboard()) return;
        theia::Hermes::instance().publish<event::KeyEvent>(Window(window_), key, scancode, action, mods);
    });

    window.set_char_callback([](GLFWwindow *window_, unsigned int codepoint) {
        theia::Dear::instance().char_callback(window_, codepoint);
        if (theia::Dear::instance().want_capture_keyboard()) return;
        theia::Hermes::instance().publish<event::CharEvent>(Window(window_), codepoint);
    });

    window.set_cursor_pos_callback([](GLFWwindow *window_, double xpos, double ypos) {
        theia::Dear::instance().cursor_pos_callback(window_, xpos, ypos);
        if (theia::Dear::instance().want_capture_mouse()) return;
        theia::Hermes::instance().publish<event::CursorPosEvent>(Window(window_), xpos, ypos);
    });

    window.set_cursor_enter_callback([](GLFWwindow *window_, int entered) {
        theia::Dear::instance().cursor_enter_callback(window_, entered);
        if (theia::Dear::instance().want_capture_mouse()) return;
        theia::Hermes::instance().publish<event::CursorEnterEvent>(Window(window_), entered == GLFW_TRUE);
    });

    window.set_mouse_button_callback([](GLFWwindow *window_, int button, int action, int mods) {
        theia::Dear::instance().mouse_button_callback(window_, button, action, mods);
        if (theia::Dear::instance().want_capture_mouse()) return;
        theia::Hermes::instance().publish<event::MouseButtonEvent>(Window(window_), button, action, mods);
    });

    window.set_scroll_callback([](GLFWwindow *window_, double xoffset, double yoffset) {
        theia::Dear::instance().scroll_callback(window_, xoffset, yoffset);
        if (theia::Dear::instance().want_capture_mouse()) return;
        theia::Hermes::instance().publish<event::ScrollEvent>(Window(window_), xoffset, yoffset);
    });

    // glfwSetJoystickCallback(
    //     [](int joy, int event) { theia::Hermes::instance().publish<event::JoystickE>(joy, event); });

    window.set_drop_callback([](GLFWwindow *window_, int count, const char **paths) {
        theia::Hermes::instance().publish<event::DropEvent>(Window(window_), count, paths);
    });
}

bool glfwpp::supports_raw_mouse_motion() { return glfwRawMouseMotionSupported(); }

std::string glfwpp::get_clipboard_string() { return glfwGetClipboardString(nullptr); }

void glfwpp::set_clipboard_string(const std::string &s) { glfwSetClipboardString(nullptr, s.c_str()); }
