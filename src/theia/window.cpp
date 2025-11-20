#include "theia/window.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdexcept>

theia::Window::Window(GLFWwindow *window)
    : window_(window) {}

theia::Window::~Window() {
    if (window_) {
        glfwDestroyWindow(window_);
    }
}

theia::Window::Window(Window &&other) noexcept
    : window_(other.window_) {
    other.window_ = nullptr;
}

theia::Window &theia::Window::operator=(Window &&other) noexcept {
    if (this != &other) {
        if (window_) {
            glfwDestroyWindow(window_);
        }
        window_ = other.window_;
        other.window_ = nullptr;
    }
    return *this;
}

void theia::Window::make_context_current() { glfwMakeContextCurrent(window_); }

bool theia::Window::should_close() const { return glfwWindowShouldClose(window_) == GLFW_TRUE; }

void theia::Window::set_should_close(bool value) { glfwSetWindowShouldClose(window_, value ? GLFW_TRUE : GLFW_FALSE); }

void theia::Window::swap_buffers() { glfwSwapBuffers(window_); }

glm::ivec2 theia::Window::size() const {
    int width, height;
    glfwGetWindowSize(window_, &width, &height);
    return {width, height};
}

void theia::Window::set_size(glm::ivec2 size) { glfwSetWindowSize(window_, size.x, size.y); }

int theia::Window::w() const { return size().x; }

int theia::Window::h() const { return size().y; }

glm::ivec4 theia::Window::frame_size() const {
    int left, top, right, bottom;
    glfwGetWindowFrameSize(window_, &left, &top, &right, &bottom);
    return {left, top, right, bottom};
}

glm::ivec2 theia::Window::framebuffer_size() const {
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    return {width, height};
}

glm::vec2 theia::Window::content_scale() const {
    float x_scale, y_scale;
    glfwGetWindowContentScale(window_, &x_scale, &y_scale);
    return {x_scale, y_scale};
}

void theia::Window::set_size_limits(glm::ivec2 min_limits, glm::ivec2 max_limits) {
    glfwSetWindowSizeLimits(window_, min_limits.x, min_limits.y, max_limits.x, max_limits.y);
}

void theia::Window::set_aspect_ratio(int numer, int denom) { glfwSetWindowAspectRatio(window_, numer, denom); }

glm::ivec2 theia::Window::position() const {
    int x, y;
    glfwGetWindowPos(window_, &x, &y);
    return {x, y};
}

void theia::Window::set_position(glm::ivec2 pos) { glfwSetWindowPos(window_, pos.x, pos.y); }

int theia::Window::x() const { return position().x; }

int theia::Window::y() const { return position().y; }

const char *theia::Window::title() const { return glfwGetWindowTitle(window_); }

void theia::Window::set_title(const std::string &title) { glfwSetWindowTitle(window_, title.c_str()); }

GLFWmonitor *theia::Window::monitor() const { return glfwGetWindowMonitor(window_); }

void theia::Window::set_monitor(GLFWmonitor *monitor, int x_pos, int y_pos, int width, int height, int refresh_rate) {
    glfwSetWindowMonitor(window_, monitor, x_pos, y_pos, width, height, refresh_rate);
}

float theia::Window::opacity() const { return glfwGetWindowOpacity(window_); }

void theia::Window::set_opacity(float opacity) { glfwSetWindowOpacity(window_, opacity); }

bool theia::Window::focused() const { return glfwGetWindowAttrib(window_, GLFW_FOCUSED) == GLFW_TRUE; }

bool theia::Window::iconified() const { return glfwGetWindowAttrib(window_, GLFW_ICONIFIED) == GLFW_TRUE; }

bool theia::Window::maximized() const { return glfwGetWindowAttrib(window_, GLFW_MAXIMIZED) == GLFW_TRUE; }

bool theia::Window::hovered() const { return glfwGetWindowAttrib(window_, GLFW_HOVERED) == GLFW_TRUE; }

bool theia::Window::visible() const { return glfwGetWindowAttrib(window_, GLFW_VISIBLE) == GLFW_TRUE; }

bool theia::Window::resizable() const { return glfwGetWindowAttrib(window_, GLFW_RESIZABLE) == GLFW_TRUE; }

bool theia::Window::decorated() const { return glfwGetWindowAttrib(window_, GLFW_DECORATED) == GLFW_TRUE; }

bool theia::Window::auto_iconify() const { return glfwGetWindowAttrib(window_, GLFW_AUTO_ICONIFY) == GLFW_TRUE; }

bool theia::Window::floating() const { return glfwGetWindowAttrib(window_, GLFW_FLOATING) == GLFW_TRUE; }

bool theia::Window::transparent_framebuffer() const {
    return glfwGetWindowAttrib(window_, GLFW_TRANSPARENT_FRAMEBUFFER) == GLFW_TRUE;
}

bool theia::Window::focused_on_show() const { return glfwGetWindowAttrib(window_, GLFW_FOCUS_ON_SHOW) == GLFW_TRUE; }

bool theia::Window::mouse_passthrough() const {
    return glfwGetWindowAttrib(window_, GLFW_MOUSE_PASSTHROUGH) == GLFW_TRUE;
}

void theia::Window::focus() { glfwFocusWindow(window_); }

void theia::Window::request_focus() { glfwRequestWindowAttention(window_); }

void theia::Window::iconify() { glfwIconifyWindow(window_); }

void theia::Window::maximize() { glfwMaximizeWindow(window_); }

void theia::Window::restore() { glfwRestoreWindow(window_); }

void theia::Window::set_visible(bool visible) {
    if (visible) {
        glfwShowWindow(window_);
    } else {
        glfwHideWindow(window_);
    }
}

void theia::Window::set_resizable(bool resizable) {
    glfwSetWindowAttrib(window_, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
}

void theia::Window::set_decorated(bool decorated) {
    glfwSetWindowAttrib(window_, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
}

void theia::Window::set_auto_iconify(bool auto_iconify) {
    glfwSetWindowAttrib(window_, GLFW_AUTO_ICONIFY, auto_iconify ? GLFW_TRUE : GLFW_FALSE);
}

void theia::Window::set_floating(bool floating) {
    glfwSetWindowAttrib(window_, GLFW_FLOATING, floating ? GLFW_TRUE : GLFW_FALSE);
}

void theia::Window::set_focus_on_show(bool focus_on_show) {
    glfwSetWindowAttrib(window_, GLFW_FOCUS_ON_SHOW, focus_on_show ? GLFW_TRUE : GLFW_FALSE);
}

void theia::Window::set_mouse_passthrough(bool enabled) {
    glfwSetWindowAttrib(window_, GLFW_MOUSE_PASSTHROUGH, enabled ? GLFW_TRUE : GLFW_FALSE);
}

GLFWwindow *theia::Window::get_native_window() const { return window_; }

void *theia::Window::user_pointer() const { return glfwGetWindowUserPointer(window_); }

void theia::Window::set_user_pointer(void *pointer) { glfwSetWindowUserPointer(window_, pointer); }

theia::WindowBuilder::WindowBuilder() = default;

theia::WindowBuilder &theia::WindowBuilder::size(int width, int height) {
    width_ = width;
    height_ = height;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::title(std::string title) {
    title_ = std::move(title);
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::monitor(GLFWmonitor *monitor) {
    monitor_ = monitor;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::share(GLFWwindow *share) {
    share_ = share;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::position(int x, int y) {
    hints_[GLFW_POSITION_X] = x;
    hints_[GLFW_POSITION_Y] = y;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::resizable(bool resizable) {
    hints_[GLFW_RESIZABLE] = resizable ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::visible(bool visible) {
    hints_[GLFW_VISIBLE] = visible ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::decorated(bool decorated) {
    hints_[GLFW_DECORATED] = decorated ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::focused(bool focused) {
    hints_[GLFW_FOCUSED] = focused ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::auto_iconify(bool auto_iconify) {
    hints_[GLFW_AUTO_ICONIFY] = auto_iconify ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::floating(bool floating) {
    hints_[GLFW_FLOATING] = floating ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::maximized(bool maximized) {
    hints_[GLFW_MAXIMIZED] = maximized ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::center_cursor(bool center_cursor) {
    hints_[GLFW_CENTER_CURSOR] = center_cursor ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::transparent_framebuffer(bool transparent) {
    hints_[GLFW_TRANSPARENT_FRAMEBUFFER] = transparent ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::focus_on_show(bool focus_on_show) {
    hints_[GLFW_FOCUS_ON_SHOW] = focus_on_show ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::scale_to_monitor(bool scale_to_monitor) {
    hints_[GLFW_SCALE_TO_MONITOR] = scale_to_monitor ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::mouse_passthrough(bool passthrough) {
    hints_[GLFW_MOUSE_PASSTHROUGH] = passthrough ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::red_bits(int bits) {
    hints_[GLFW_RED_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::green_bits(int bits) {
    hints_[GLFW_GREEN_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::blue_bits(int bits) {
    hints_[GLFW_BLUE_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::alpha_bits(int bits) {
    hints_[GLFW_ALPHA_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::depth_bits(int bits) {
    hints_[GLFW_DEPTH_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::stencil_bits(int bits) {
    hints_[GLFW_STENCIL_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::accum_red_bits(int bits) {
    hints_[GLFW_ACCUM_RED_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::accum_green_bits(int bits) {
    hints_[GLFW_ACCUM_GREEN_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::accum_blue_bits(int bits) {
    hints_[GLFW_ACCUM_BLUE_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::accum_alpha_bits(int bits) {
    hints_[GLFW_ACCUM_ALPHA_BITS] = bits;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::aux_buffers(int buffers) {
    hints_[GLFW_AUX_BUFFERS] = buffers;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::stereo(bool stereo) {
    hints_[GLFW_STEREO] = stereo ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::samples(int samples) {
    hints_[GLFW_SAMPLES] = samples;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::srgb_capable(bool srgb_capable) {
    hints_[GLFW_SRGB_CAPABLE] = srgb_capable ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::double_buffer(bool double_buffer) {
    hints_[GLFW_DOUBLEBUFFER] = double_buffer ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::refresh_rate(int refresh_rate) {
    hints_[GLFW_REFRESH_RATE] = refresh_rate;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::client_api(int api) {
    hints_[GLFW_CLIENT_API] = api;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::context_creation_api(int api) {
    hints_[GLFW_CONTEXT_CREATION_API] = api;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::context_version(int major, int minor) {
    hints_[GLFW_CONTEXT_VERSION_MAJOR] = major;
    hints_[GLFW_CONTEXT_VERSION_MINOR] = minor;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::context_robustness(int robustness) {
    hints_[GLFW_CONTEXT_ROBUSTNESS] = robustness;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::context_release_behavior(int behavior) {
    hints_[GLFW_CONTEXT_RELEASE_BEHAVIOR] = behavior;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::context_no_error(bool no_error) {
    hints_[GLFW_CONTEXT_NO_ERROR] = no_error ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::opengl_profile(int profile) {
    hints_[GLFW_OPENGL_PROFILE] = profile;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::opengl_forward_compat(bool forward_compat) {
    hints_[GLFW_OPENGL_FORWARD_COMPAT] = forward_compat ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

theia::WindowBuilder &theia::WindowBuilder::opengl_debug_context(bool debug) {
    hints_[GLFW_OPENGL_DEBUG_CONTEXT] = debug ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

std::unique_ptr<theia::Window> theia::WindowBuilder::build() const {
    glfwDefaultWindowHints();

    for (const auto &[key, value] : hints_) {
        glfwWindowHint(key, value);
    }

    GLFWwindow *window = glfwCreateWindow(width_, height_, title_.c_str(), monitor_, share_);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    return std::make_unique<theia::Window>(window);
}
