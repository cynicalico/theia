#pragma once

#include "glfwpp/monitor.hpp"
#include "theia/hermes.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace glfwpp {
enum class InputMode {
    StickyKeys = GLFW_STICKY_KEYS,
    StickyMouseButtons = GLFW_STICKY_MOUSE_BUTTONS,
    LockKeyMods = GLFW_LOCK_KEY_MODS,
    RawMouseMotion = GLFW_RAW_MOUSE_MOTION,
};

enum class CursorMode {
    Normal = GLFW_CURSOR_NORMAL,
    Hidden = GLFW_CURSOR_HIDDEN,
    Disabled = GLFW_CURSOR_DISABLED,
    Captured = GLFW_CURSOR_CAPTURED,
};

class Window {
public:
    explicit Window(GLFWwindow *window);
    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    Window(Window &&other) noexcept;
    Window &operator=(Window &&other) noexcept;

    void make_context_current();

    [[nodiscard]] bool should_close() const;
    void set_should_close(bool value);

    void swap_buffers();

    [[nodiscard]] glm::ivec2 size() const;
    void set_size(glm::ivec2 size);
    [[nodiscard]] int w() const;
    [[nodiscard]] int h() const;
    [[nodiscard]] glm::ivec4 frame_size() const;

    [[nodiscard]] glm::ivec2 framebuffer_size() const;

    [[nodiscard]] glm::vec2 content_scale() const;

    void set_size_limits(glm::ivec2 min_limits, glm::ivec2 max_limits);
    void set_aspect_ratio(int numer, int denom);

    [[nodiscard]] glm::ivec2 position() const;
    void set_position(glm::ivec2 pos);
    [[nodiscard]] int x() const;
    [[nodiscard]] int y() const;

    [[nodiscard]] const char *title() const;
    void set_title(const std::string &title);

    void set_icon(const std::filesystem::path &path);

    [[nodiscard]] std::optional<Monitor> monitor() const;
    void set_monitor(std::optional<Monitor> monitor, int xpos, int ypos, int width, int height, int refresh_rate);

    [[nodiscard]] float opacity() const;
    void set_opacity(float opacity);

    [[nodiscard]] bool focused() const;
    [[nodiscard]] bool iconified() const;
    [[nodiscard]] bool maximized() const;
    [[nodiscard]] bool hovered() const;
    [[nodiscard]] bool visible() const;
    [[nodiscard]] bool resizable() const;
    [[nodiscard]] bool decorated() const;
    [[nodiscard]] bool auto_iconify() const;
    [[nodiscard]] bool floating() const;
    [[nodiscard]] bool transparent_framebuffer() const;
    [[nodiscard]] bool focused_on_show() const;
    [[nodiscard]] bool mouse_passthrough() const;
    void focus();
    void request_focus();
    void iconify();
    void maximize();
    void restore();
    void set_visible(bool visible);
    void set_resizable(bool resizable);
    void set_decorated(bool decorated);
    void set_auto_iconify(bool auto_iconify);
    void set_floating(bool floating);
    void set_focus_on_show(bool focus_on_show);
    void set_mouse_passthrough(bool enabled);

    void set_input_mode(InputMode mode, bool value);
    [[nodiscard]] bool get_input_mode(InputMode mode) const;

    void set_cursor_mode(CursorMode mode);
    [[nodiscard]] CursorMode get_cursor_mode() const;

    // TODO: cursors

    void set_close_callback(GLFWwindowclosefun callback);
    void set_size_callback(GLFWwindowsizefun callback);
    void set_framebuffer_size_callback(GLFWframebuffersizefun callback);
    void set_content_scale_callback(GLFWwindowcontentscalefun callback);
    void set_pos_callback(GLFWwindowposfun callback);
    void set_iconify_callback(GLFWwindowiconifyfun callback);
    void set_maximize_callback(GLFWwindowmaximizefun callback);
    void set_focus_callback(GLFWwindowfocusfun callback);
    void set_refresh_callback(GLFWwindowrefreshfun callback);

    void set_key_callback(GLFWkeyfun callback);
    void set_char_callback(GLFWcharfun callback);
    void set_cursor_pos_callback(GLFWcursorposfun callback);
    void set_cursor_enter_callback(GLFWcursorenterfun callback);
    void set_mouse_button_callback(GLFWmousebuttonfun callback);
    void set_scroll_callback(GLFWscrollfun callback);
    void set_drop_callback(GLFWdropfun callback);

    [[nodiscard]] void *user_pointer() const;
    void set_user_pointer(void *ptr);

    [[nodiscard]] GLFWwindow *handle() const;

private:
    GLFWwindow *handle_ = nullptr;
};

enum class ClientApi {
    OpenGL = GLFW_OPENGL_API,
    OpenGLES = GLFW_OPENGL_ES_API,
    None = GLFW_NO_API,
};

enum class ContextCreationApi {
    Native = GLFW_NATIVE_CONTEXT_API,
    Egl = GLFW_EGL_CONTEXT_API,
    Mesa = GLFW_OSMESA_CONTEXT_API,
};

enum class ContextRobustness {
    NoResetNotification = GLFW_NO_RESET_NOTIFICATION,
    LoseContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET,
    None = GLFW_NO_ROBUSTNESS,
};

enum class ReleaseBehavior {
    Any = GLFW_ANY_RELEASE_BEHAVIOR,
    Flush = GLFW_RELEASE_BEHAVIOR_FLUSH,
    None = GLFW_RELEASE_BEHAVIOR_NONE,
};

enum class OpenGLProfile {
    Core = GLFW_OPENGL_CORE_PROFILE,
    Compat = GLFW_OPENGL_COMPAT_PROFILE,
    Any = GLFW_OPENGL_ANY_PROFILE,
};

class WindowBuilder {
public:
    WindowBuilder();

    // Basic properties
    WindowBuilder &size(glm::ivec2 size);
    WindowBuilder &title(std::string title);
    WindowBuilder &monitor(const Monitor &monitor);
    WindowBuilder &share(const Window &share);

    // Window related hints
    WindowBuilder &position(glm::ivec2 position);
    WindowBuilder &resizable(bool resizable);
    WindowBuilder &visible(bool visible);
    WindowBuilder &decorated(bool decorated);
    WindowBuilder &focused(bool focused);
    WindowBuilder &auto_iconify(bool auto_iconify);
    WindowBuilder &floating(bool floating);
    WindowBuilder &maximized(bool maximized);
    WindowBuilder &center_cursor(bool center_cursor);
    WindowBuilder &transparent_framebuffer(bool transparent);
    WindowBuilder &focus_on_show(bool focus_on_show);
    WindowBuilder &scale_to_monitor(bool scale_to_monitor);
    WindowBuilder &mouse_passthrough(bool passthrough);

    // Framebuffer related hints
    WindowBuilder &red_bits(int bits);
    WindowBuilder &green_bits(int bits);
    WindowBuilder &blue_bits(int bits);
    WindowBuilder &alpha_bits(int bits);
    WindowBuilder &depth_bits(int bits);
    WindowBuilder &stencil_bits(int bits);
    WindowBuilder &accum_red_bits(int bits);
    WindowBuilder &accum_green_bits(int bits);
    WindowBuilder &accum_blue_bits(int bits);
    WindowBuilder &accum_alpha_bits(int bits);
    WindowBuilder &aux_buffers(int buffers);
    WindowBuilder &stereo(bool stereo);
    WindowBuilder &samples(int samples);
    WindowBuilder &srgb_capable(bool srgb_capable);
    WindowBuilder &double_buffer(bool double_buffer);

    // Monitor related hints
    WindowBuilder &refresh_rate(int refresh_rate);
    WindowBuilder &match_vidmode(const Monitor &monitor);

    // Context related hints
    WindowBuilder &client_api(ClientApi api);
    WindowBuilder &context_creation_api(ContextCreationApi api);
    WindowBuilder &context_version(int major, int minor);
    WindowBuilder &context_robustness(ContextRobustness robustness);
    WindowBuilder &context_release_behavior(ReleaseBehavior behavior);
    WindowBuilder &context_no_error(bool no_error);
    WindowBuilder &opengl_profile(OpenGLProfile profile);
    WindowBuilder &opengl_forward_compat(bool forward_compat);
    WindowBuilder &opengl_debug_context(bool debug);

    [[nodiscard]] std::unique_ptr<Window> build() const;

private:
    int width_ = 1280;
    int height_ = 720;
    std::string title_ = "Theia Application";
    GLFWmonitor *monitor_ = nullptr;
    GLFWwindow *share_ = nullptr;

    std::unordered_map<int, int> hints_;
};

namespace event {
struct WindowCloseEvent {
    MAKE_HERMES_ID(glfwpp::event::WindowCloseEvent);
    Window window;
};

struct WindowSizeEvent {
    MAKE_HERMES_ID(glfwpp::event::WindowSizeEvent);
    Window window;
    int width;
    int height;
};

struct FramebufferSizeEvent {
    MAKE_HERMES_ID(glfwpp::event::FramebufferSizeEvent);
    Window window;
    int width;
    int height;
};

struct WindowContentScaleEvent {
    MAKE_HERMES_ID(glfwpp::event::WindowContentScaleEvent);
    Window window;
    float xscale;
    float yscale;
};

struct WindowPosEvent {
    MAKE_HERMES_ID(glfwpp::event::WindowPosEvent);
    Window window;
    int xpos;
    int ypos;
};

struct WindowIconifyEvent {
    MAKE_HERMES_ID(glfwpp::event::WindowIconifyEvent);
    Window window;
    bool iconified;
};

struct WindowMaximizeEvent {
    MAKE_HERMES_ID(glfwpp::event::WindowMaximizeEvent);
    Window window;
    bool maximized;
};

struct WindowFocusEvent {
    MAKE_HERMES_ID(glfwpp::event::WindowFocusEvent);
    Window window;
    bool focused;
};

struct WindowRefreshEvent {
    MAKE_HERMES_ID(glfwpp::event::WindowRefreshEvent);
    Window window;
};
} // namespace event

void set_window_callbacks(Window &window);
} // namespace glfwpp
