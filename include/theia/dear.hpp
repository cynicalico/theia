#pragma once

/* IMPORTANT: Naming conventions in this file do not match the rest of the codebase.
 *            This is deliberate to keep it consistent with Dear ImGui's naming conventions.
 */

#include "glfwpp/window.hpp"
#include "theia/logger.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string_view>

namespace theia {
class Dear {
    class Context_;

    struct Begin_;
    struct Combo_;
    struct ListBox_;
    struct MenuBar_;
    struct MainMenuBar_;
    struct Menu_;
    struct Tooltip_;
    struct ItemTooltip_;
    struct Popup_;
    struct Modal_;
    struct PopupContextItem_;
    struct PopupContextWindow_;
    struct PopupContextVoid_;
    struct Table_;
    struct TabBar_;
    struct TabItem_;
    struct DragDropSource_;
    struct DragDropTarget_;
    struct Disabled_;
    struct Group_;

public:
    /*******************
     * GENERAL HELPERS *
     *******************/

    static Context_ Context(const glfwpp::Window &window);

    static void NewFrame();
    static void Render();

    static bool WantCaptureMouse();
    static bool WantCaptureKeyboard();

    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void CharCallback(GLFWwindow *window, unsigned int codepoint);
    static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
    static void CursorEnterCallback(GLFWwindow *window, int entered);
    static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    static void WindowFocusCallback(GLFWwindow *window, int focused);
    static void MonitorCallback(GLFWmonitor *monitor, int event);

    /**********************
     * AUTO SCOPE HELPERS *
     **********************/

    static Begin_ Begin(std::string_view title, bool *open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

    static Group_ Group();

    static Combo_
    Combo(std::string_view label, std::string_view preview_value, ImGuiComboFlags flags = ImGuiComboFlags_None);

    static ListBox_ ListBox(std::string_view label, const ImVec2 &size = ImVec2(0, 0));

    static MenuBar_ MenuBar();

    static MainMenuBar_ MainMenuBar();

    static Menu_ Menu(std::string_view label, bool enabled = true);

    static Tooltip_ Tooltip();

    static ItemTooltip_ ItemTooltip();

    static Popup_ Popup(std::string_view str_id, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

    static Modal_
    Modal(std::string_view str_id, bool *p_open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

    static PopupContextItem_ PopupContextItem(std::string_view str_id,
                                              ImGuiPopupFlags popup_flags = ImGuiPopupFlags_MouseButtonRight);

    static PopupContextWindow_ PopupContextWindow(std::string_view str_id,
                                                  ImGuiPopupFlags popup_flags = ImGuiPopupFlags_MouseButtonRight);

    static PopupContextVoid_ PopupContextVoid(std::string_view str_id,
                                              ImGuiPopupFlags popup_flags = ImGuiPopupFlags_MouseButtonRight);

    static Table_ Table(std::string_view str_id,
                        int columns,
                        ImGuiTableFlags flags = ImGuiTableFlags_None,
                        const ImVec2 &outer_size = ImVec2(0, 0),
                        float inner_width = 0.0f);

    static TabBar_ TabBar(std::string_view str_id, ImGuiTabBarFlags flags = ImGuiTabBarFlags_None);

    static TabItem_
    TabItem(std::string_view label, bool *p_open = nullptr, ImGuiTabItemFlags flags = ImGuiTabItemFlags_None);

    static DragDropSource_ DragDropSource(ImGuiDragDropFlags flags = ImGuiDragDropFlags_None);

    static DragDropTarget_ DragDropTarget();

    static Disabled_ Disabled(bool disabled = true);

    /****************
     * TEXT HELPERS *
     ****************/

    static void TextUnformatted(const std::string_view text);

    template <typename... T>
    static void Text(fmt::format_string<T...> fmt, T &&...args);

    template <typename... T>
    static void TextColored(const ImVec4 &col, fmt::format_string<T...> fmt, T &&...args);

    template <typename... T>
    static void TextDisabled(fmt::format_string<T...> fmt, T &&...args);

    template <typename... T>
    static void TextWrapped(fmt::format_string<T...> fmt, T &&...args);

    template <typename... T>
    static void LabelText(const std::string &label, fmt::format_string<T...> fmt, T &&...args);

    template <typename... T>
    static void BulletText(fmt::format_string<T...> fmt, T &&...args);

    template <typename... T>
    static void SeparatorText(fmt::format_string<T...> fmt, T &&...args);

private:
    class Context_ {
    public:
        explicit Context_(GLFWwindow *window);

        ~Context_();

        Context_(const Context_ &other) = delete;
        Context_ &operator=(const Context_ &other) = delete;

        Context_(Context_ &&other) noexcept;
        Context_ &operator=(Context_ &&other) noexcept;

    private:
        ImGuiContext *ctx_;
    };

    template <typename Base, bool ForceDtor = false>
    struct ScopeWrapper_ {
    protected:
        const bool ok_;

    public:
        explicit constexpr ScopeWrapper_(const bool ok) noexcept
            : ok_{ok} {}

        ~ScopeWrapper_() noexcept {
            if constexpr (!ForceDtor)
                if (!ok_) return;
            Base::dtor();
        }

        ScopeWrapper_(const ScopeWrapper_ &) = delete;
        ScopeWrapper_ &operator=(const ScopeWrapper_ &) = delete;

        ScopeWrapper_(ScopeWrapper_ &&other) noexcept = delete;
        ScopeWrapper_ &operator=(ScopeWrapper_ &&other) noexcept = delete;

        template <typename F>
        constexpr bool operator&&(F &&body) const noexcept {
            if (ok_) body();
            return ok_;
        }

        explicit constexpr operator bool() const noexcept { return ok_; }
    };

    struct Begin_ : ScopeWrapper_<Begin_, true> {
        Begin_(const std::string_view title, bool *open, const ImGuiWindowFlags flags) noexcept
            : ScopeWrapper_(ImGui::Begin(title.data(), open, flags)) {}

        static void dtor() noexcept { ImGui::End(); }
    };

    // TODO: Font
    // TODO: Styles (this one will be complicated)
    // TODO: ItemFlag
    // TODO: ItemWidth
    // TODO: TextWrapPos

    struct Group_ : ScopeWrapper_<Group_> {
        Group_() noexcept
            : ScopeWrapper_(true) {
            ImGui::BeginGroup();
        }

        static void dtor() noexcept { ImGui::EndGroup(); }
    };

    // TODO: ID

    struct Combo_ : ScopeWrapper_<Combo_> {
        Combo_(const std::string_view label, const std::string_view preview_value, const ImGuiComboFlags flags) noexcept
            : ScopeWrapper_(ImGui::BeginCombo(label.data(), preview_value.data(), flags)) {}

        static void dtor() noexcept { ImGui::EndCombo(); }
    };

    // TODO: TreeNode/Ex
    // TODO: MultiSelect

    struct ListBox_ : ScopeWrapper_<ListBox_> {
        ListBox_(const std::string_view label, const ImVec2 &size) noexcept
            : ScopeWrapper_(ImGui::BeginListBox(label.data(), size)) {}

        static void dtor() noexcept { ImGui::EndListBox(); }
    };

    struct MenuBar_ : ScopeWrapper_<MenuBar_> {
        MenuBar_() noexcept
            : ScopeWrapper_(ImGui::BeginMenuBar()) {}

        static void dtor() noexcept { ImGui::EndMenuBar(); }
    };

    struct MainMenuBar_ : ScopeWrapper_<MainMenuBar_> {
        MainMenuBar_() noexcept
            : ScopeWrapper_(ImGui::BeginMainMenuBar()) {}

        static void dtor() noexcept { ImGui::EndMainMenuBar(); }
    };

    struct Menu_ : ScopeWrapper_<Menu_> {
        Menu_(const std::string_view label, const bool enabled) noexcept
            : ScopeWrapper_(ImGui::BeginMenu(label.data(), enabled)) {}

        static void dtor() noexcept { ImGui::EndMenu(); }
    };

    struct Tooltip_ : ScopeWrapper_<Tooltip_> {
        Tooltip_() noexcept
            : ScopeWrapper_(ImGui::BeginTooltip()) {}

        static void dtor() noexcept { ImGui::EndTooltip(); }
    };

    struct ItemTooltip_ : ScopeWrapper_<ItemTooltip_> {
        ItemTooltip_() noexcept
            : ScopeWrapper_(ImGui::BeginItemTooltip()) {}

        static void dtor() noexcept { ImGui::EndTooltip(); }
    };

    struct Popup_ : ScopeWrapper_<Popup_> {
        Popup_(const std::string_view str_id, const ImGuiWindowFlags flags) noexcept
            : ScopeWrapper_(ImGui::BeginPopup(str_id.data(), flags)) {}

        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct Modal_ : ScopeWrapper_<Modal_> {
        Modal_(const std::string_view str_id, bool *p_open, const ImGuiWindowFlags flags) noexcept
            : ScopeWrapper_(ImGui::BeginPopupModal(str_id.data(), p_open, flags)) {}

        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct PopupContextItem_ : ScopeWrapper_<PopupContextItem_> {
        PopupContextItem_(const std::string_view str_id, const ImGuiPopupFlags popup_flags) noexcept
            : ScopeWrapper_(ImGui::BeginPopupContextItem(str_id.data(), popup_flags)) {}

        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct PopupContextWindow_ : ScopeWrapper_<PopupContextWindow_> {
        PopupContextWindow_(const std::string_view str_id, const ImGuiPopupFlags popup_flags) noexcept
            : ScopeWrapper_(ImGui::BeginPopupContextWindow(str_id.data(), popup_flags)) {}

        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct PopupContextVoid_ : ScopeWrapper_<PopupContextVoid_> {
        PopupContextVoid_(const std::string_view str_id, const ImGuiPopupFlags popup_flags) noexcept
            : ScopeWrapper_(ImGui::BeginPopupContextVoid(str_id.data(), popup_flags)) {}

        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct Table_ : ScopeWrapper_<Table_> {
        Table_(const std::string_view str_id,
               const int columns,
               const ImGuiTableFlags flags,
               const ImVec2 &outer_size,
               const float inner_width) noexcept
            : ScopeWrapper_(ImGui::BeginTable(str_id.data(), columns, flags, outer_size, inner_width)) {}

        static void dtor() noexcept { ImGui::EndTable(); }
    };

    struct TabBar_ : ScopeWrapper_<TabBar_> {
        TabBar_(const std::string_view str_id, ImGuiTabBarFlags flags) noexcept
            : ScopeWrapper_(ImGui::BeginTabBar(str_id.data(), flags)) {}

        static void dtor() noexcept { ImGui::EndTabBar(); }
    };

    struct TabItem_ : ScopeWrapper_<TabItem_> {
        TabItem_(const std::string_view label, bool *p_open, ImGuiTabItemFlags flags) noexcept
            : ScopeWrapper_(ImGui::BeginTabItem(label.data(), p_open, flags)) {}

        static void dtor() noexcept { ImGui::EndTabItem(); }
    };

    struct DragDropSource_ : ScopeWrapper_<DragDropSource_> {
        DragDropSource_(ImGuiDragDropFlags flags) noexcept
            : ScopeWrapper_(ImGui::BeginDragDropSource(flags)) {}

        static void dtor() noexcept { ImGui::EndDragDropSource(); }
    };

    struct DragDropTarget_ : ScopeWrapper_<DragDropTarget_> {
        DragDropTarget_() noexcept
            : ScopeWrapper_(ImGui::BeginDragDropTarget()) {}

        static void dtor() noexcept { ImGui::EndDragDropTarget(); }
    };

    struct Disabled_ : ScopeWrapper_<Disabled_> {
        Disabled_(const bool disabled) noexcept
            : ScopeWrapper_(true) {
            ImGui::BeginDisabled(disabled);
        }

        static void dtor() noexcept { ImGui::EndDisabled(); }
    };

    // TODO: ClipRect
};

inline Dear::Context_ Dear::Context(const glfwpp::Window &window) { return Context_(window.handle()); }

inline void Dear::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

inline void Dear::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

inline bool Dear::WantCaptureMouse() { return ImGui::GetIO().WantCaptureMouse; }

inline bool Dear::WantCaptureKeyboard() { return ImGui::GetIO().WantCaptureKeyboard; }

inline void Dear::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

inline void Dear::CharCallback(GLFWwindow *window, unsigned int codepoint) {
    ImGui_ImplGlfw_CharCallback(window, codepoint);
}

inline void Dear::CursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
}

inline void Dear::CursorEnterCallback(GLFWwindow *window, int entered) {
    ImGui_ImplGlfw_CursorEnterCallback(window, entered);
}

inline void Dear::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

inline void Dear::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

inline void Dear::WindowFocusCallback(GLFWwindow *window, int focused) {
    ImGui_ImplGlfw_WindowFocusCallback(window, focused);
}

inline void Dear::MonitorCallback(GLFWmonitor *monitor, int event) { ImGui_ImplGlfw_MonitorCallback(monitor, event); }

inline Dear::Begin_ Dear::Begin(const std::string_view title, bool *open, ImGuiWindowFlags flags) {
    return {title, open, flags};
}

inline Dear::Group_ Dear::Group() { return {}; }

inline Dear::Combo_
Dear::Combo(const std::string_view label, const std::string_view preview_value, ImGuiComboFlags flags) {
    return {label, preview_value, flags};
}

inline Dear::ListBox_ Dear::ListBox(std::string_view label, const ImVec2 &size) { return {label, size}; }

inline Dear::MenuBar_ Dear::MenuBar() { return {}; }

inline Dear::MainMenuBar_ Dear::MainMenuBar() { return {}; }

inline Dear::Menu_ Dear::Menu(const std::string_view label, const bool enabled) { return {label, enabled}; }

inline Dear::Tooltip_ Dear::Tooltip() { return {}; }

inline Dear::ItemTooltip_ Dear::ItemTooltip() { return {}; }

inline Dear::Popup_ Dear::Popup(const std::string_view str_id, ImGuiWindowFlags flags) { return {str_id, flags}; }

inline Dear::Modal_ Dear::Modal(const std::string_view str_id, bool *p_open, ImGuiWindowFlags flags) {
    return {str_id, p_open, flags};
}

inline Dear::PopupContextItem_ Dear::PopupContextItem(const std::string_view str_id, ImGuiPopupFlags popup_flags) {
    return {str_id, popup_flags};
}

inline Dear::PopupContextWindow_ Dear::PopupContextWindow(const std::string_view str_id, ImGuiPopupFlags popup_flags) {
    return {str_id, popup_flags};
}

inline Dear::PopupContextVoid_ Dear::PopupContextVoid(const std::string_view str_id, ImGuiPopupFlags popup_flags) {
    return {str_id, popup_flags};
}

inline Dear::Table_ Dear::Table(
    const std::string_view str_id, int columns, ImGuiTableFlags flags, const ImVec2 &outer_size, float inner_width) {
    return {str_id, columns, flags, outer_size, inner_width};
}

inline Dear::TabBar_ Dear::TabBar(const std::string_view str_id, ImGuiTabBarFlags flags) { return {str_id, flags}; }

inline Dear::TabItem_ Dear::TabItem(const std::string_view label, bool *p_open, ImGuiTabItemFlags flags) {
    return {label, p_open, flags};
}

inline Dear::DragDropSource_ Dear::DragDropSource(ImGuiDragDropFlags flags) { return {flags}; }

inline Dear::DragDropTarget_ Dear::DragDropTarget() { return {}; }

inline Dear::Disabled_ Dear::Disabled(const bool disabled) { return {disabled}; }

inline void Dear::TextUnformatted(const std::string_view text) {
    ImGui::TextUnformatted(text.data(), text.data() + text.size());
}

template <typename... T>
void Dear::Text(fmt::format_string<T...> fmt, T &&...args) {
    const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
    TextUnformatted(formatted);
}

template <typename... T>
void Dear::TextColored(const ImVec4 &col, fmt::format_string<T...> fmt, T &&...args) {
    ImGui::PushStyleColor(ImGuiCol_Text, col);
    const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
    TextUnformatted(formatted);
    ImGui::PopStyleColor();
}

template <typename... T>
void Dear::TextDisabled(fmt::format_string<T...> fmt, T &&...args) {
    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
    const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
    TextUnformatted(formatted);
    ImGui::PopStyleColor();
}

template <typename... T>
void Dear::TextWrapped(fmt::format_string<T...> fmt, T &&...args) {
    ImGui::PushTextWrapPos(0.0f);
    const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
    TextUnformatted(formatted);
    ImGui::PopTextWrapPos();
}

template <typename... T>
void Dear::LabelText(const std::string &label, fmt::format_string<T...> fmt, T &&...args) {
    const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
    ImGui::LabelText(label.c_str(), formatted.c_str());
}

template <typename... T>
void Dear::BulletText(fmt::format_string<T...> fmt, T &&...args) {
    ImGui::Bullet();
    const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
    TextUnformatted(formatted);
}

template <typename... T>
void Dear::SeparatorText(fmt::format_string<T...> fmt, T &&...args) {
    const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
    ImGui::SeparatorText(formatted.c_str());
}

inline Dear::Context_::Context_(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ctx_ = ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    if (!ImGui_ImplGlfw_InitForOpenGL(window, false))
        throw std::runtime_error("Failed to initialize ImGui GLFW backend");

    if (!ImGui_ImplOpenGL3_Init("#version 130")) throw std::runtime_error("Failed to initialize ImGui OpenGL backend");

    THEIA_LOG_DEBUG("Dear initialized, ImGui v{}", ImGui::GetVersion());
}

inline Dear::Context_::~Context_() {
    if (ctx_) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext(ctx_);
    }
}

inline Dear::Context_::Context_(Context_ &&other) noexcept
    : ctx_(other.ctx_) {}

inline Dear::Context_ &Dear::Context_::operator=(Context_ &&other) noexcept {
    if (this != &other) {
        ctx_ = other.ctx_;
        other.ctx_ = nullptr;
    }
    return *this;
}
} // namespace theia
