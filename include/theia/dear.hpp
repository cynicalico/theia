#pragma once

#include "theia/logger.hpp"

#include "imgui.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string_view>

namespace theia {
class Dear {
    Dear() = default;

    template <typename Base, bool ForceDtor = false>
    struct ScopeWrapper {
        using wrapped_type = Base;
        using self_type = ScopeWrapper<Base>;

        static constexpr bool force_dtor = ForceDtor;

    protected:
        const bool ok_;

    public:
        explicit constexpr ScopeWrapper(const bool ok) noexcept
            : ok_{ok} {}

        ~ScopeWrapper() noexcept {
            if constexpr (!force_dtor)
                if (!ok_) return;
            Base::dtor();
        }

        ScopeWrapper(const ScopeWrapper &) = delete;
        ScopeWrapper &operator=(const ScopeWrapper &) = delete;

        ScopeWrapper(ScopeWrapper &&other) noexcept = delete;
        ScopeWrapper &operator=(ScopeWrapper &&other) noexcept = delete;

        template <typename F>
        constexpr bool operator&&(F &&body) const noexcept {
            if (ok_) body();
            return ok_;
        }

        explicit constexpr operator bool() const noexcept { return ok_; }
    };

    struct Begin : ScopeWrapper<Begin, true> {
        explicit Begin(const std::string_view title, bool *open, const ImGuiWindowFlags flags) noexcept
            : ScopeWrapper(ImGui::Begin(title.data(), open, flags)) {}
        static void dtor() noexcept { ImGui::End(); }
    };

public:
    Dear(const Dear &other) = delete;
    Dear &operator=(const Dear &other) = delete;

    Dear(Dear &&other) = delete;
    Dear &operator=(Dear &&other) = delete;

    static void init(GLFWwindow *window);
    static void shutdown();
    static Dear &instance();

    void new_frame();
    void render();

    bool want_capture_mouse();
    bool want_capture_keyboard();

    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void char_callback(GLFWwindow *window, unsigned int codepoint);
    void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);
    void cursor_enter_callback(GLFWwindow *window, int entered);
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    void window_focus_callback(GLFWwindow *window, int focused);
    void monitor_callback(GLFWmonitor *monitor, int event);

    Begin begin(std::string_view title, bool *open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
};
} // namespace theia
