#pragma once

#include <memory>
#include <string>
#include <unordered_map>

// Forward declarations
struct GLFWwindow;
struct GLFWmonitor;

namespace theia {

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

    [[nodiscard]] GLFWwindow *get_native_window() const;

private:
    GLFWwindow *window_ = nullptr;
};

class WindowBuilder {
public:
    WindowBuilder();

    // Basic properties
    WindowBuilder &size(int width, int height);
    WindowBuilder &title(std::string title);
    WindowBuilder &monitor(GLFWmonitor *monitor);
    WindowBuilder &share(GLFWwindow *share);

    // Window related hints
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
    WindowBuilder &mouse_passthrough(bool passthrough); // GLFW 3.4+

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

    WindowBuilder &set_hint_(int hint, int value);
};

} // namespace theia
