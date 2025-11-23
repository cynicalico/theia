#pragma once

#include "theia/hermes.hpp"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

struct GLFWcursor;
struct GLFWmonitor;
struct GLFWvidmode;
struct GLFWwindow;

namespace glfwpp {
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

    [[nodiscard]] GLFWmonitor *monitor() const;
    void set_monitor(GLFWmonitor *monitor, int x_pos, int y_pos, int width, int height, int refresh_rate);

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

    void set_input_mode(int mode, int value);
    [[nodiscard]] bool get_input_mode(int mode) const;

    // TODO: cursors

    [[nodiscard]] void *user_pointer() const;
    void set_user_pointer(void *ptr);

    [[nodiscard]] GLFWwindow *handle() const;

private:
    GLFWwindow *handle_ = nullptr;
};

class WindowBuilder {
public:
    WindowBuilder();

    // Basic properties
    WindowBuilder &size(glm::ivec2 size);
    WindowBuilder &title(std::string title);
    WindowBuilder &monitor(GLFWmonitor *monitor);
    WindowBuilder &share(GLFWwindow *share);

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
    WindowBuilder &match_vidmode(const GLFWvidmode *vidmode);

    // Context related hints
    WindowBuilder &client_api(int api);
    WindowBuilder &context_creation_api(int api);
    WindowBuilder &context_version(int major, int minor);
    WindowBuilder &context_robustness(int robustness);
    WindowBuilder &context_release_behavior(int behavior);
    WindowBuilder &context_no_error(bool no_error);
    WindowBuilder &opengl_profile(int profile);
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
struct WindowCloseE {
    MAKE_HERMES_ID(glfwpp::event::WindowCloseE);
    GLFWwindow *window;
};

struct WindowSizeE {
    MAKE_HERMES_ID(glfwpp::event::WindowSizeE);
    GLFWwindow *window;
    int width;
    int height;
};

struct FramebufferSizeE {
    MAKE_HERMES_ID(glfwpp::event::FramebufferSizeE);
    GLFWwindow *window;
    int width;
    int height;
};

struct WindowContentScaleE {
    MAKE_HERMES_ID(glfwpp::event::WindowContentScaleE);
    GLFWwindow *window;
    float xscale;
    float yscale;
};

struct WindowPosE {
    MAKE_HERMES_ID(glfwpp::event::WindowPosE);
    GLFWwindow *window;
    int xpos;
    int ypos;
};

struct WindowIconifyE {
    MAKE_HERMES_ID(glfwpp::event::WindowIconifyE);
    GLFWwindow *window;
    bool iconified;
};

struct WindowMaximizeE {
    MAKE_HERMES_ID(glfwpp::event::WindowMaximizeE);
    GLFWwindow *window;
    bool maximized;
};

struct WindowFocusE {
    MAKE_HERMES_ID(glfwpp::event::WindowFocusE);
    GLFWwindow *window;
    bool focused;
};

struct WindowRefreshE {
    MAKE_HERMES_ID(glfwpp::event::WindowRefreshE);
    GLFWwindow *window;
};
} // namespace event

void set_window_callbacks(GLFWwindow *window);
} // namespace glfwpp
