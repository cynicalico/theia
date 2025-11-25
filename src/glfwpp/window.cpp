#include "glfwpp/window.hpp"
#include "glfwpp/input.hpp"
#include "theia/io.hpp"

#include <stdexcept>

glfwpp::Window::Window(GLFWwindow *window)
    : handle_(window) {
    set_window_callbacks(*this);
    set_input_callbacks(*this);
}

glfwpp::Window::~Window() {
    if (handle_) glfwDestroyWindow(handle_);
}

glfwpp::Window::Window(Window &&other) noexcept
    : handle_(other.handle_) {
    other.handle_ = nullptr;
    set_window_callbacks(*this);
    set_input_callbacks(*this);
}

glfwpp::Window &glfwpp::Window::operator=(Window &&other) noexcept {
    if (this != &other) {
        if (handle_) glfwDestroyWindow(handle_);
        handle_ = other.handle_;
        other.handle_ = nullptr;
        set_window_callbacks(*this);
        set_input_callbacks(*this);
    }
    return *this;
}

void glfwpp::Window::make_context_current() { glfwMakeContextCurrent(handle_); }

bool glfwpp::Window::should_close() const { return glfwWindowShouldClose(handle_) == GLFW_TRUE; }

void glfwpp::Window::set_should_close(bool value) { glfwSetWindowShouldClose(handle_, value ? GLFW_TRUE : GLFW_FALSE); }

void glfwpp::Window::swap_buffers() { glfwSwapBuffers(handle_); }

glm::ivec2 glfwpp::Window::size() const {
    int width, height;
    glfwGetWindowSize(handle_, &width, &height);
    return {width, height};
}

void glfwpp::Window::set_size(glm::ivec2 size) { glfwSetWindowSize(handle_, size.x, size.y); }

int glfwpp::Window::w() const { return size().x; }

int glfwpp::Window::h() const { return size().y; }

glm::ivec4 glfwpp::Window::frame_size() const {
    int left, top, right, bottom;
    glfwGetWindowFrameSize(handle_, &left, &top, &right, &bottom);
    return {left, top, right, bottom};
}

glm::ivec2 glfwpp::Window::framebuffer_size() const {
    int width, height;
    glfwGetFramebufferSize(handle_, &width, &height);
    return {width, height};
}

glm::vec2 glfwpp::Window::content_scale() const {
    float x_scale, y_scale;
    glfwGetWindowContentScale(handle_, &x_scale, &y_scale);
    return {x_scale, y_scale};
}

void glfwpp::Window::set_size_limits(glm::ivec2 min_limits, glm::ivec2 max_limits) {
    glfwSetWindowSizeLimits(handle_, min_limits.x, min_limits.y, max_limits.x, max_limits.y);
}

void glfwpp::Window::set_aspect_ratio(int numer, int denom) { glfwSetWindowAspectRatio(handle_, numer, denom); }

glm::ivec2 glfwpp::Window::position() const {
    int x, y;
    glfwGetWindowPos(handle_, &x, &y);
    return {x, y};
}

void glfwpp::Window::set_position(glm::ivec2 pos) { glfwSetWindowPos(handle_, pos.x, pos.y); }

int glfwpp::Window::x() const { return position().x; }

int glfwpp::Window::y() const { return position().y; }

const char *glfwpp::Window::title() const { return glfwGetWindowTitle(handle_); }

void glfwpp::Window::set_title(const std::string &title) { glfwSetWindowTitle(handle_, title.c_str()); }

static void read_image(std::vector<std::vector<std::byte>> &image_data,
                       std::vector<GLFWimage> &images,
                       const std::filesystem::path &path) {
    auto [bytes, w, h] = theia::read_image_bytes(path);
    if (bytes.empty()) return;
    image_data.push_back(std::move(bytes));
    images.push_back(GLFWimage{w, h, reinterpret_cast<unsigned char *>(image_data.back().data())});
}

void glfwpp::Window::set_icon(const std::filesystem::path &path) {
    std::vector<std::vector<std::byte>> image_data{};
    std::vector<GLFWimage> images{};

    if (std::filesystem::is_directory(path)) {
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                read_image(image_data, images, entry.path());
            }
        }
    } else {
        read_image(image_data, images, path);
    }

    if (!images.empty()) glfwSetWindowIcon(handle_, images.size(), images.data());
}

std::optional<glfwpp::Monitor> glfwpp::Window::monitor() const {
    GLFWmonitor *glfw_monitor = glfwGetWindowMonitor(handle_);
    if (!glfw_monitor) return std::nullopt;
    return Monitor{glfw_monitor};
}

void glfwpp::Window::set_monitor(
    std::optional<Monitor> monitor, int xpos, int ypos, int width, int height, int refresh_rate) {
    GLFWmonitor *glfw_monitor = monitor ? monitor->handle() : nullptr;
    glfwSetWindowMonitor(handle_, glfw_monitor, xpos, ypos, width, height, refresh_rate);
}

float glfwpp::Window::opacity() const { return glfwGetWindowOpacity(handle_); }

void glfwpp::Window::set_opacity(float opacity) { glfwSetWindowOpacity(handle_, opacity); }

bool glfwpp::Window::focused() const { return glfwGetWindowAttrib(handle_, GLFW_FOCUSED) == GLFW_TRUE; }

bool glfwpp::Window::iconified() const { return glfwGetWindowAttrib(handle_, GLFW_ICONIFIED) == GLFW_TRUE; }

bool glfwpp::Window::maximized() const { return glfwGetWindowAttrib(handle_, GLFW_MAXIMIZED) == GLFW_TRUE; }

bool glfwpp::Window::hovered() const { return glfwGetWindowAttrib(handle_, GLFW_HOVERED) == GLFW_TRUE; }

bool glfwpp::Window::visible() const { return glfwGetWindowAttrib(handle_, GLFW_VISIBLE) == GLFW_TRUE; }

bool glfwpp::Window::resizable() const { return glfwGetWindowAttrib(handle_, GLFW_RESIZABLE) == GLFW_TRUE; }

bool glfwpp::Window::decorated() const { return glfwGetWindowAttrib(handle_, GLFW_DECORATED) == GLFW_TRUE; }

bool glfwpp::Window::auto_iconify() const { return glfwGetWindowAttrib(handle_, GLFW_AUTO_ICONIFY) == GLFW_TRUE; }

bool glfwpp::Window::floating() const { return glfwGetWindowAttrib(handle_, GLFW_FLOATING) == GLFW_TRUE; }

bool glfwpp::Window::transparent_framebuffer() const {
    return glfwGetWindowAttrib(handle_, GLFW_TRANSPARENT_FRAMEBUFFER) == GLFW_TRUE;
}

bool glfwpp::Window::focused_on_show() const { return glfwGetWindowAttrib(handle_, GLFW_FOCUS_ON_SHOW) == GLFW_TRUE; }

bool glfwpp::Window::mouse_passthrough() const {
    return glfwGetWindowAttrib(handle_, GLFW_MOUSE_PASSTHROUGH) == GLFW_TRUE;
}

void glfwpp::Window::focus() { glfwFocusWindow(handle_); }

void glfwpp::Window::request_focus() { glfwRequestWindowAttention(handle_); }

void glfwpp::Window::iconify() { glfwIconifyWindow(handle_); }

void glfwpp::Window::maximize() { glfwMaximizeWindow(handle_); }

void glfwpp::Window::restore() { glfwRestoreWindow(handle_); }

void glfwpp::Window::set_visible(bool visible) {
    if (visible) {
        glfwShowWindow(handle_);
    } else {
        glfwHideWindow(handle_);
    }
}

void glfwpp::Window::set_resizable(bool resizable) {
    glfwSetWindowAttrib(handle_, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
}

void glfwpp::Window::set_decorated(bool decorated) {
    glfwSetWindowAttrib(handle_, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
}

void glfwpp::Window::set_auto_iconify(bool auto_iconify) {
    glfwSetWindowAttrib(handle_, GLFW_AUTO_ICONIFY, auto_iconify ? GLFW_TRUE : GLFW_FALSE);
}

void glfwpp::Window::set_floating(bool floating) {
    glfwSetWindowAttrib(handle_, GLFW_FLOATING, floating ? GLFW_TRUE : GLFW_FALSE);
}

void glfwpp::Window::set_focus_on_show(bool focus_on_show) {
    glfwSetWindowAttrib(handle_, GLFW_FOCUS_ON_SHOW, focus_on_show ? GLFW_TRUE : GLFW_FALSE);
}

void glfwpp::Window::set_mouse_passthrough(bool enabled) {
    glfwSetWindowAttrib(handle_, GLFW_MOUSE_PASSTHROUGH, enabled ? GLFW_TRUE : GLFW_FALSE);
}

void glfwpp::Window::set_input_mode(InputMode mode, bool value) {
    glfwSetInputMode(handle_, static_cast<int>(mode), value ? GLFW_TRUE : GLFW_FALSE);
}

bool glfwpp::Window::get_input_mode(InputMode mode) const {
    return glfwGetInputMode(handle_, static_cast<int>(mode)) == GLFW_TRUE;
}

void glfwpp::Window::set_cursor_mode(CursorMode mode) {
    glfwSetInputMode(handle_, GLFW_CURSOR, static_cast<int>(mode));
}

glfwpp::CursorMode glfwpp::Window::get_cursor_mode() const {
    return static_cast<CursorMode>(glfwGetInputMode(handle_, GLFW_CURSOR));
}

void glfwpp::Window::set_cursor(const Cursor &cursor) { glfwSetCursor(handle_, cursor.handle()); }

void glfwpp::Window::set_close_callback(GLFWwindowclosefun callback) { glfwSetWindowCloseCallback(handle_, callback); }

void glfwpp::Window::set_size_callback(GLFWwindowsizefun callback) { glfwSetWindowSizeCallback(handle_, callback); }

void glfwpp::Window::set_framebuffer_size_callback(GLFWframebuffersizefun callback) {
    glfwSetFramebufferSizeCallback(handle_, callback);
}

void glfwpp::Window::set_content_scale_callback(GLFWwindowcontentscalefun callback) {
    glfwSetWindowContentScaleCallback(handle_, callback);
}

void glfwpp::Window::set_pos_callback(GLFWwindowposfun callback) { glfwSetWindowPosCallback(handle_, callback); }

void glfwpp::Window::set_iconify_callback(GLFWwindowiconifyfun callback) {
    glfwSetWindowIconifyCallback(handle_, callback);
}

void glfwpp::Window::set_maximize_callback(GLFWwindowmaximizefun callback) {
    glfwSetWindowMaximizeCallback(handle_, callback);
}

void glfwpp::Window::set_focus_callback(GLFWwindowfocusfun callback) { glfwSetWindowFocusCallback(handle_, callback); }

void glfwpp::Window::set_refresh_callback(GLFWwindowrefreshfun callback) {
    glfwSetWindowRefreshCallback(handle_, callback);
}

void glfwpp::Window::set_key_callback(GLFWkeyfun callback) { glfwSetKeyCallback(handle_, callback); }

void glfwpp::Window::set_char_callback(GLFWcharfun callback) { glfwSetCharCallback(handle_, callback); }

void glfwpp::Window::set_cursor_pos_callback(GLFWcursorposfun callback) { glfwSetCursorPosCallback(handle_, callback); }

void glfwpp::Window::set_cursor_enter_callback(GLFWcursorenterfun callback) {
    glfwSetCursorEnterCallback(handle_, callback);
}

void glfwpp::Window::set_mouse_button_callback(GLFWmousebuttonfun callback) {
    glfwSetMouseButtonCallback(handle_, callback);
}

void glfwpp::Window::set_scroll_callback(GLFWscrollfun callback) { glfwSetScrollCallback(handle_, callback); }

void glfwpp::Window::set_drop_callback(GLFWdropfun callback) { glfwSetDropCallback(handle_, callback); }

void *glfwpp::Window::user_pointer() const { return glfwGetWindowUserPointer(handle_); }

void glfwpp::Window::set_user_pointer(void *ptr) { glfwSetWindowUserPointer(handle_, ptr); }

GLFWwindow *glfwpp::Window::handle() const { return handle_; }

glfwpp::WindowBuilder::WindowBuilder() = default;

glfwpp::WindowBuilder &glfwpp::WindowBuilder::size(glm::ivec2 size) {
    width_ = size.x;
    height_ = size.y;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::title(std::string title) {
    title_ = std::move(title);
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::monitor(const Monitor &monitor) {
    monitor_ = monitor.handle();
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::share(const Window &share) {
    share_ = share.handle();
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::position(glm::ivec2 position) {
    hints_[GLFW_POSITION_X] = position.x;
    hints_[GLFW_POSITION_Y] = position.y;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::resizable(bool resizable) {
    hints_[GLFW_RESIZABLE] = resizable ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::visible(bool visible) {
    hints_[GLFW_VISIBLE] = visible ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::decorated(bool decorated) {
    hints_[GLFW_DECORATED] = decorated ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::focused(bool focused) {
    hints_[GLFW_FOCUSED] = focused ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::auto_iconify(bool auto_iconify) {
    hints_[GLFW_AUTO_ICONIFY] = auto_iconify ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::floating(bool floating) {
    hints_[GLFW_FLOATING] = floating ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::maximized(bool maximized) {
    hints_[GLFW_MAXIMIZED] = maximized ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::center_cursor(bool center_cursor) {
    hints_[GLFW_CENTER_CURSOR] = center_cursor ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::transparent_framebuffer(bool transparent) {
    hints_[GLFW_TRANSPARENT_FRAMEBUFFER] = transparent ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::focus_on_show(bool focus_on_show) {
    hints_[GLFW_FOCUS_ON_SHOW] = focus_on_show ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::scale_to_monitor(bool scale_to_monitor) {
    hints_[GLFW_SCALE_TO_MONITOR] = scale_to_monitor ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::mouse_passthrough(bool passthrough) {
    hints_[GLFW_MOUSE_PASSTHROUGH] = passthrough ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::red_bits(int bits) {
    hints_[GLFW_RED_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::green_bits(int bits) {
    hints_[GLFW_GREEN_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::blue_bits(int bits) {
    hints_[GLFW_BLUE_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::alpha_bits(int bits) {
    hints_[GLFW_ALPHA_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::depth_bits(int bits) {
    hints_[GLFW_DEPTH_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::stencil_bits(int bits) {
    hints_[GLFW_STENCIL_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::accum_red_bits(int bits) {
    hints_[GLFW_ACCUM_RED_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::accum_green_bits(int bits) {
    hints_[GLFW_ACCUM_GREEN_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::accum_blue_bits(int bits) {
    hints_[GLFW_ACCUM_BLUE_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::accum_alpha_bits(int bits) {
    hints_[GLFW_ACCUM_ALPHA_BITS] = bits;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::aux_buffers(int buffers) {
    hints_[GLFW_AUX_BUFFERS] = buffers;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::stereo(bool stereo) {
    hints_[GLFW_STEREO] = stereo ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::samples(int samples) {
    hints_[GLFW_SAMPLES] = samples;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::srgb_capable(bool srgb_capable) {
    hints_[GLFW_SRGB_CAPABLE] = srgb_capable ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::double_buffer(bool double_buffer) {
    hints_[GLFW_DOUBLEBUFFER] = double_buffer ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::refresh_rate(int refresh_rate) {
    hints_[GLFW_REFRESH_RATE] = refresh_rate;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::match_vidmode(const Monitor &monitor) {
    red_bits(monitor.red_bits());
    green_bits(monitor.green_bits());
    blue_bits(monitor.blue_bits());
    refresh_rate(monitor.refresh_rate());
    size(monitor.size());
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::client_api(ClientApi api) {
    hints_[GLFW_CLIENT_API] = static_cast<int>(api);
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::context_creation_api(ContextCreationApi api) {
    hints_[GLFW_CONTEXT_CREATION_API] = static_cast<int>(api);
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::context_version(int major, int minor) {
    hints_[GLFW_CONTEXT_VERSION_MAJOR] = major;
    hints_[GLFW_CONTEXT_VERSION_MINOR] = minor;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::context_robustness(ContextRobustness robustness) {
    hints_[GLFW_CONTEXT_ROBUSTNESS] = static_cast<int>(robustness);
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::context_release_behavior(ReleaseBehavior behavior) {
    hints_[GLFW_CONTEXT_RELEASE_BEHAVIOR] = static_cast<int>(behavior);
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::context_no_error(bool no_error) {
    hints_[GLFW_CONTEXT_NO_ERROR] = no_error ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::opengl_profile(OpenGLProfile profile) {
    hints_[GLFW_OPENGL_PROFILE] = static_cast<int>(profile);
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::opengl_forward_compat(bool forward_compat) {
    hints_[GLFW_OPENGL_FORWARD_COMPAT] = forward_compat ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

glfwpp::WindowBuilder &glfwpp::WindowBuilder::opengl_debug_context(bool debug) {
    hints_[GLFW_OPENGL_DEBUG_CONTEXT] = debug ? GLFW_TRUE : GLFW_FALSE;
    return *this;
}

std::unique_ptr<glfwpp::Window> glfwpp::WindowBuilder::build() const {
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

void glfwpp::set_window_callbacks(Window &window) {
    window.set_close_callback(
        [](GLFWwindow *window_) { theia::Hermes::instance().publish<event::WindowCloseEvent>(Window(window_)); });

    window.set_size_callback([](GLFWwindow *window_, int width, int height) {
        theia::Hermes::instance().publish<event::WindowSizeEvent>(Window(window_), width, height);
    });

    window.set_framebuffer_size_callback([](GLFWwindow *window_, int width, int height) {
        theia::Hermes::instance().publish<event::FramebufferSizeEvent>(Window(window_), width, height);
    });

    window.set_content_scale_callback([](GLFWwindow *window_, float xscale, float yscale) {
        theia::Hermes::instance().publish<event::WindowContentScaleEvent>(Window(window_), xscale, yscale);
    });

    window.set_pos_callback([](GLFWwindow *window_, int xpos, int ypos) {
        theia::Hermes::instance().publish<event::WindowPosEvent>(Window(window_), xpos, ypos);
    });

    window.set_iconify_callback([](GLFWwindow *window_, int iconified) {
        theia::Hermes::instance().publish<event::WindowIconifyEvent>(Window(window_), iconified == GLFW_TRUE);
    });

    window.set_maximize_callback([](GLFWwindow *window_, int maximized) {
        theia::Hermes::instance().publish<event::WindowMaximizeEvent>(Window(window_), maximized == GLFW_TRUE);
    });

    window.set_focus_callback([](GLFWwindow *window_, int focused) {
        theia::Hermes::instance().publish<event::WindowFocusEvent>(Window(window_), focused == GLFW_TRUE);
    });

    window.set_refresh_callback(
        [](GLFWwindow *window_) { theia::Hermes::instance().publish<event::WindowRefreshEvent>(Window(window_)); });
}
