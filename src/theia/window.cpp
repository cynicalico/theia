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

bool Window::should_close() const { return glfwWindowShouldClose(window_) == GLFW_TRUE; }

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
    hints_[GLFW_RESIZABLE] = resizable ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::visible(bool visible) {
    hints_[GLFW_VISIBLE] = visible ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::decorated(bool decorated) {
    hints_[GLFW_DECORATED] = decorated ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::focused(bool focused) {
    hints_[GLFW_FOCUSED] = focused ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::auto_iconify(bool auto_iconify) {
    hints_[GLFW_AUTO_ICONIFY] = auto_iconify ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::floating(bool floating) {
    hints_[GLFW_FLOATING] = floating ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::maximized(bool maximized) {
    hints_[GLFW_MAXIMIZED] = maximized ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::center_cursor(bool center_cursor) {
    hints_[GLFW_CENTER_CURSOR] = center_cursor ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::transparent_framebuffer(bool transparent) {
    hints_[GLFW_TRANSPARENT_FRAMEBUFFER] = transparent ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::focus_on_show(bool focus_on_show) {
    hints_[GLFW_FOCUS_ON_SHOW] = focus_on_show ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::scale_to_monitor(bool scale_to_monitor) {
    hints_[GLFW_SCALE_TO_MONITOR] = scale_to_monitor ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::mouse_passthrough(bool passthrough) {
    hints_[GLFW_MOUSE_PASSTHROUGH] = passthrough ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::red_bits(int bits) {
    hints_[GLFW_RED_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::green_bits(int bits) {
    hints_[GLFW_GREEN_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::blue_bits(int bits) {
    hints_[GLFW_BLUE_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::alpha_bits(int bits) {
    hints_[GLFW_ALPHA_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::depth_bits(int bits) {
    hints_[GLFW_DEPTH_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::stencil_bits(int bits) {
    hints_[GLFW_STENCIL_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::accum_red_bits(int bits) {
    hints_[GLFW_ACCUM_RED_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::accum_green_bits(int bits) {
    hints_[GLFW_ACCUM_GREEN_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::accum_blue_bits(int bits) {
    hints_[GLFW_ACCUM_BLUE_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::accum_alpha_bits(int bits) {
    hints_[GLFW_ACCUM_ALPHA_BITS] = bits;
    return *this;
}

WindowBuilder &WindowBuilder::aux_buffers(int buffers) {
    hints_[GLFW_AUX_BUFFERS] = buffers;
    return *this;
}

WindowBuilder &WindowBuilder::stereo(bool stereo) {
    hints_[GLFW_STEREO] = stereo ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::samples(int samples) {
    hints_[GLFW_SAMPLES] = samples;
    return *this;
}

WindowBuilder &WindowBuilder::srgb_capable(bool srgb_capable) {
    hints_[GLFW_SRGB_CAPABLE] = srgb_capable ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::double_buffer(bool double_buffer) {
    hints_[GLFW_DOUBLEBUFFER] = double_buffer ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::refresh_rate(int refresh_rate) {
    hints_[GLFW_REFRESH_RATE] = refresh_rate;
    return *this;
}

WindowBuilder &WindowBuilder::client_api(int api) {
    hints_[GLFW_CLIENT_API] = api;
    return *this;
}

WindowBuilder &WindowBuilder::context_creation_api(int api) {
    hints_[GLFW_CONTEXT_CREATION_API] = api;
    return *this;
}

WindowBuilder &WindowBuilder::context_version(int major, int minor) {
    hints_[GLFW_CONTEXT_VERSION_MAJOR] = major;
    hints_[GLFW_CONTEXT_VERSION_MINOR] = minor;
    return *this;
}

WindowBuilder &WindowBuilder::context_robustness(int robustness) {
    hints_[GLFW_CONTEXT_ROBUSTNESS] = robustness;
    return *this;
}

WindowBuilder &WindowBuilder::context_release_behavior(int behavior) {
    hints_[GLFW_CONTEXT_RELEASE_BEHAVIOR] = behavior;
    return *this;
}

WindowBuilder &WindowBuilder::context_no_error(bool no_error) {
    hints_[GLFW_CONTEXT_NO_ERROR] = no_error ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::opengl_profile(int profile) {
    hints_[GLFW_OPENGL_PROFILE] = profile;
    return *this;
}

WindowBuilder &WindowBuilder::opengl_forward_compat(bool forward_compat) {
    hints_[GLFW_OPENGL_FORWARD_COMPAT] = forward_compat ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

WindowBuilder &WindowBuilder::opengl_debug_context(bool debug) {
    hints_[GLFW_OPENGL_DEBUG_CONTEXT] = debug ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

std::unique_ptr<Window> WindowBuilder::build() const {
    glfwDefaultWindowHints();

    for (const auto &[key, value] : hints_) {
        glfwWindowHint(key, value);
    }

    GLFWwindow *window = glfwCreateWindow(width_, height_, title_.c_str(), monitor_, share_);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    return std::make_unique<Window>(window);
}
} // namespace theia
