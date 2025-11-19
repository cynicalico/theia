#include "theia/window.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace theia {
Window::Window(GLFWwindow *window)
    : window_(window) {}

Window::~Window() {
    if (window_) {
        glfwDestroyWindow(window_);
    }
}

Window::Window(Window &&other) noexcept
    : window_(other.window_) {
    other.window_ = nullptr;
}

Window &Window::operator=(Window &&other) noexcept {
    if (this != &other) {
        if (window_) {
            glfwDestroyWindow(window_);
        }
        window_ = other.window_;
        other.window_ = nullptr;
    }
    return *this;
}

void Window::make_context_current() { glfwMakeContextCurrent(window_); }

bool Window::should_close() const { return glfwWindowShouldClose(window_); }

void Window::set_should_close(bool value) { glfwSetWindowShouldClose(window_, value ? GLFW_TRUE : GLFW_FALSE); }

void Window::swap_buffers() { glfwSwapBuffers(window_); }

GLFWwindow *Window::get_native_window() const { return window_; }

WindowBuilder::WindowBuilder() = default;

WindowBuilder &WindowBuilder::size(int width, int height) {
    width_ = width;
    height_ = height;
    return *this;
}

WindowBuilder &WindowBuilder::title(std::string title) {
    title_ = std::move(title);
    return *this;
}

WindowBuilder &WindowBuilder::monitor(GLFWmonitor *monitor) {
    monitor_ = monitor;
    return *this;
}

WindowBuilder &WindowBuilder::share(GLFWwindow *share) {
    share_ = share;
    return *this;
}

WindowBuilder &WindowBuilder::resizable(bool resizable) {
    return set_hint_(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::visible(bool visible) {
    return set_hint_(GLFW_VISIBLE, visible ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::decorated(bool decorated) {
    return set_hint_(GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::focused(bool focused) {
    return set_hint_(GLFW_FOCUSED, focused ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::auto_iconify(bool auto_iconify) {
    return set_hint_(GLFW_AUTO_ICONIFY, auto_iconify ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::floating(bool floating) {
    return set_hint_(GLFW_FLOATING, floating ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::maximized(bool maximized) {
    return set_hint_(GLFW_MAXIMIZED, maximized ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::center_cursor(bool center_cursor) {
    return set_hint_(GLFW_CENTER_CURSOR, center_cursor ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::transparent_framebuffer(bool transparent) {
    return set_hint_(GLFW_TRANSPARENT_FRAMEBUFFER, transparent ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::focus_on_show(bool focus_on_show) {
    return set_hint_(GLFW_FOCUS_ON_SHOW, focus_on_show ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::scale_to_monitor(bool scale_to_monitor) {
    return set_hint_(GLFW_SCALE_TO_MONITOR, scale_to_monitor ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::mouse_passthrough(bool passthrough) {
    return set_hint_(GLFW_MOUSE_PASSTHROUGH, passthrough ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::red_bits(int bits) { return set_hint_(GLFW_RED_BITS, bits); }

WindowBuilder &WindowBuilder::green_bits(int bits) { return set_hint_(GLFW_GREEN_BITS, bits); }

WindowBuilder &WindowBuilder::blue_bits(int bits) { return set_hint_(GLFW_BLUE_BITS, bits); }

WindowBuilder &WindowBuilder::alpha_bits(int bits) { return set_hint_(GLFW_ALPHA_BITS, bits); }

WindowBuilder &WindowBuilder::depth_bits(int bits) { return set_hint_(GLFW_DEPTH_BITS, bits); }

WindowBuilder &WindowBuilder::stencil_bits(int bits) { return set_hint_(GLFW_STENCIL_BITS, bits); }

WindowBuilder &WindowBuilder::accum_red_bits(int bits) { return set_hint_(GLFW_ACCUM_RED_BITS, bits); }

WindowBuilder &WindowBuilder::accum_green_bits(int bits) { return set_hint_(GLFW_ACCUM_GREEN_BITS, bits); }

WindowBuilder &WindowBuilder::accum_blue_bits(int bits) { return set_hint_(GLFW_ACCUM_BLUE_BITS, bits); }

WindowBuilder &WindowBuilder::accum_alpha_bits(int bits) { return set_hint_(GLFW_ACCUM_ALPHA_BITS, bits); }

WindowBuilder &WindowBuilder::aux_buffers(int buffers) { return set_hint_(GLFW_AUX_BUFFERS, buffers); }

WindowBuilder &WindowBuilder::stereo(bool stereo) { return set_hint_(GLFW_STEREO, stereo ? GLFW_TRUE : GLFW_FALSE); }

WindowBuilder &WindowBuilder::samples(int samples) { return set_hint_(GLFW_SAMPLES, samples); }

WindowBuilder &WindowBuilder::srgb_capable(bool srgb_capable) {
    return set_hint_(GLFW_SRGB_CAPABLE, srgb_capable ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::double_buffer(bool double_buffer) {
    return set_hint_(GLFW_DOUBLEBUFFER, double_buffer ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::refresh_rate(int refresh_rate) { return set_hint_(GLFW_REFRESH_RATE, refresh_rate); }

WindowBuilder &WindowBuilder::client_api(int api) { return set_hint_(GLFW_CLIENT_API, api); }

WindowBuilder &WindowBuilder::context_creation_api(int api) { return set_hint_(GLFW_CONTEXT_CREATION_API, api); }

WindowBuilder &WindowBuilder::context_version(int major, int minor) {
    set_hint_(GLFW_CONTEXT_VERSION_MAJOR, major);
    return set_hint_(GLFW_CONTEXT_VERSION_MINOR, minor);
}

WindowBuilder &WindowBuilder::context_robustness(int robustness) {
    return set_hint_(GLFW_CONTEXT_ROBUSTNESS, robustness);
}

WindowBuilder &WindowBuilder::context_release_behavior(int behavior) {
    return set_hint_(GLFW_CONTEXT_RELEASE_BEHAVIOR, behavior);
}

WindowBuilder &WindowBuilder::context_no_error(bool no_error) {
    return set_hint_(GLFW_CONTEXT_NO_ERROR, no_error ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::opengl_profile(int profile) { return set_hint_(GLFW_OPENGL_PROFILE, profile); }

WindowBuilder &WindowBuilder::opengl_forward_compat(bool forward_compat) {
    return set_hint_(GLFW_OPENGL_FORWARD_COMPAT, forward_compat ? GLFW_TRUE : GLFW_FALSE);
}

WindowBuilder &WindowBuilder::opengl_debug_context(bool debug) {
    return set_hint_(GLFW_OPENGL_DEBUG_CONTEXT, debug ? GLFW_TRUE : GLFW_FALSE);
}

std::unique_ptr<Window> WindowBuilder::build() const {
    glfwDefaultWindowHints();

    GLFWwindow *window = glfwCreateWindow(width_, height_, title_.c_str(), monitor_, share_);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    return std::make_unique<Window>(window);
}

WindowBuilder &WindowBuilder::set_hint_(int hint, int value) {
    hints_[hint] = value;
    return *this;
}
} // namespace theia
