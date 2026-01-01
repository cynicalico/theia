#pragma once

/* IMPORTANT: Naming conventions in this file do not match the rest of the codebase.
 *            This is deliberate to keep it consistent with Dear ImGui's naming conventions.
 */

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
    protected:
        const bool ok_;

    public:
        explicit constexpr ScopeWrapper(const bool ok) noexcept
            : ok_{ok} {}

        ~ScopeWrapper() noexcept {
            if constexpr (!ForceDtor)
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

    struct Begin_ : ScopeWrapper<Begin_, true> {
        Begin_(const std::string_view title, bool *open, const ImGuiWindowFlags flags) noexcept
            : ScopeWrapper(ImGui::Begin(title.data(), open, flags)) {}
        static void dtor() noexcept { ImGui::End(); }
    };

    // TODO: Font
    // TODO: Styles (this one will be complicated)
    // TODO: ItemFlag
    // TODO: ItemWidth
    // TODO: TextWrapPos

    struct Group_ : ScopeWrapper<Group_> {
        Group_() noexcept
            : ScopeWrapper(true) {
            ImGui::BeginGroup();
        }
        static void dtor() noexcept { ImGui::EndGroup(); }
    };

    // TODO: ID

    struct Combo_ : ScopeWrapper<Combo_> {
        Combo_(const std::string_view label, const std::string_view preview_value, const ImGuiComboFlags flags) noexcept
            : ScopeWrapper(ImGui::BeginCombo(label.data(), preview_value.data(), flags)) {}
        static void dtor() noexcept { ImGui::EndCombo(); }
    };

    // TODO: TreeNode/Ex
    // TODO: MultiSelect

    struct ListBox_ : ScopeWrapper<ListBox_> {
        ListBox_(const std::string_view label, const ImVec2 &size) noexcept
            : ScopeWrapper(ImGui::BeginListBox(label.data(), size)) {}
        static void dtor() noexcept { ImGui::EndListBox(); }
    };

    struct MenuBar_ : ScopeWrapper<MenuBar_> {
        MenuBar_() noexcept
            : ScopeWrapper(ImGui::BeginMenuBar()) {}
        static void dtor() noexcept { ImGui::EndMenuBar(); }
    };

    struct MainMenuBar_ : ScopeWrapper<MainMenuBar_> {
        MainMenuBar_() noexcept
            : ScopeWrapper(ImGui::BeginMainMenuBar()) {}
        static void dtor() noexcept { ImGui::EndMainMenuBar(); }
    };

    struct Menu_ : ScopeWrapper<Menu_> {
        Menu_(const std::string_view label, const bool enabled) noexcept
            : ScopeWrapper(ImGui::BeginMenu(label.data(), enabled)) {}
        static void dtor() noexcept { ImGui::EndMenu(); }
    };

    struct Tooltip_ : ScopeWrapper<Tooltip_> {
        Tooltip_() noexcept
            : ScopeWrapper(ImGui::BeginTooltip()) {}
        static void dtor() noexcept { ImGui::EndTooltip(); }
    };

    struct ItemTooltip_ : ScopeWrapper<ItemTooltip_> {
        ItemTooltip_() noexcept
            : ScopeWrapper(ImGui::BeginItemTooltip()) {}
        static void dtor() noexcept { ImGui::EndTooltip(); }
    };

    struct Popup_ : ScopeWrapper<Popup_> {
        Popup_(const std::string_view str_id, const ImGuiWindowFlags flags) noexcept
            : ScopeWrapper(ImGui::BeginPopup(str_id.data(), flags)) {}
        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct Modal_ : ScopeWrapper<Modal_> {
        Modal_(const std::string_view str_id, bool *p_open, const ImGuiWindowFlags flags) noexcept
            : ScopeWrapper(ImGui::BeginPopupModal(str_id.data(), p_open, flags)) {}
        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct PopupContextItem_ : ScopeWrapper<PopupContextItem_> {
        PopupContextItem_(const std::string_view str_id, const ImGuiPopupFlags popup_flags) noexcept
            : ScopeWrapper(ImGui::BeginPopupContextItem(str_id.data(), popup_flags)) {}
        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct PopupContextWindow_ : ScopeWrapper<PopupContextWindow_> {
        PopupContextWindow_(const std::string_view str_id, const ImGuiPopupFlags popup_flags) noexcept
            : ScopeWrapper(ImGui::BeginPopupContextWindow(str_id.data(), popup_flags)) {}
        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct PopupContextVoid_ : ScopeWrapper<PopupContextVoid_> {
        PopupContextVoid_(const std::string_view str_id, const ImGuiPopupFlags popup_flags) noexcept
            : ScopeWrapper(ImGui::BeginPopupContextVoid(str_id.data(), popup_flags)) {}
        static void dtor() noexcept { ImGui::EndPopup(); }
    };

    struct Table_ : ScopeWrapper<Table_> {
        Table_(const std::string_view str_id,
               const int columns,
               const ImGuiTableFlags flags,
               const ImVec2 &outer_size,
               const float inner_width) noexcept
            : ScopeWrapper(ImGui::BeginTable(str_id.data(), columns, flags, outer_size, inner_width)) {}
        static void dtor() noexcept { ImGui::EndTable(); }
    };

    struct TabBar_ : ScopeWrapper<TabBar_> {
        TabBar_(const std::string_view str_id, ImGuiTabBarFlags flags) noexcept
            : ScopeWrapper(ImGui::BeginTabBar(str_id.data(), flags)) {}
        static void dtor() noexcept { ImGui::EndTabBar(); }
    };

    struct TabItem_ : ScopeWrapper<TabItem_> {
        TabItem_(const std::string_view label, bool *p_open, ImGuiTabItemFlags flags) noexcept
            : ScopeWrapper(ImGui::BeginTabItem(label.data(), p_open, flags)) {}
        static void dtor() noexcept { ImGui::EndTabItem(); }
    };

    struct DragDropSource_ : ScopeWrapper<DragDropSource_> {
        DragDropSource_(ImGuiDragDropFlags flags) noexcept
            : ScopeWrapper(ImGui::BeginDragDropSource(flags)) {}
        static void dtor() noexcept { ImGui::EndDragDropSource(); }
    };

    struct DragDropTarget_ : ScopeWrapper<DragDropTarget_> {
        DragDropTarget_() noexcept
            : ScopeWrapper(ImGui::BeginDragDropTarget()) {}
        static void dtor() noexcept { ImGui::EndDragDropTarget(); }
    };

    struct Disabled_ : ScopeWrapper<Disabled_> {
        Disabled_(const bool disabled) noexcept
            : ScopeWrapper(true) {
            ImGui::BeginDisabled(disabled);
        }
        static void dtor() noexcept { ImGui::EndDisabled(); }
    };

    // TODO: ClipRect

public:
    Dear(const Dear &other) = delete;
    Dear &operator=(const Dear &other) = delete;

    Dear(Dear &&other) = delete;
    Dear &operator=(Dear &&other) = delete;

    static void Init(GLFWwindow *window);
    static void Shutdown();
    static Dear &Instance();

    void NewFrame();
    void Render();

    bool WantCaptureMouse();
    bool WantCaptureKeyboard();

    void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void CharCallback(GLFWwindow *window, unsigned int codepoint);
    void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
    void CursorEnterCallback(GLFWwindow *window, int entered);
    void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    void WindowFocusCallback(GLFWwindow *window, int focused);
    void MonitorCallback(GLFWmonitor *monitor, int event);

    /**********************
     * AUTO SCOPE HELPERS *
     **********************/

    Begin_ Begin(const std::string_view title, bool *open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None) {
        return {title, open, flags};
    }

    Combo_ Combo(const std::string_view label,
                 const std::string_view preview_value,
                 ImGuiComboFlags flags = ImGuiComboFlags_None) {
        return {label, preview_value, flags};
    }

    ListBox_ ListBox(std::string_view label, const ImVec2 &size = ImVec2(0, 0)) { return {label, size}; }

    MenuBar_ MenuBar() { return {}; }

    MainMenuBar_ MainMenuBar() { return {}; }

    Menu_ Menu(const std::string_view label, const bool enabled = true) { return {label, enabled}; }

    Tooltip_ Tooltip() { return {}; }

    ItemTooltip_ ItemTooltip() { return {}; }

    Popup_ Popup(const std::string_view str_id, ImGuiWindowFlags flags = ImGuiWindowFlags_None) {
        return {str_id, flags};
    }

    Modal_
    Modal(const std::string_view str_id, bool *p_open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None) {
        return {str_id, p_open, flags};
    }

    PopupContextItem_ PopupContextItem(const std::string_view str_id,
                                       ImGuiPopupFlags popup_flags = ImGuiPopupFlags_MouseButtonRight) {
        return {str_id, popup_flags};
    }

    PopupContextWindow_ PopupContextWindow(const std::string_view str_id,
                                           ImGuiPopupFlags popup_flags = ImGuiPopupFlags_MouseButtonRight) {
        return {str_id, popup_flags};
    }

    PopupContextVoid_ PopupContextVoid(const std::string_view str_id,
                                       ImGuiPopupFlags popup_flags = ImGuiPopupFlags_MouseButtonRight) {
        return {str_id, popup_flags};
    }

    Table_ Table(const std::string_view str_id,
                 int columns,
                 ImGuiTableFlags flags = ImGuiTableFlags_None,
                 const ImVec2 &outer_size = ImVec2(0, 0),
                 float inner_width = 0.0f) {
        return {str_id, columns, flags, outer_size, inner_width};
    }

    TabBar_ TabBar(const std::string_view str_id, ImGuiTabBarFlags flags = ImGuiTabBarFlags_None) {
        return {str_id, flags};
    }

    TabItem_
    TabItem(const std::string_view label, bool *p_open = nullptr, ImGuiTabItemFlags flags = ImGuiTabItemFlags_None) {
        return {label, p_open, flags};
    }

    DragDropSource_ DragDropSource(ImGuiDragDropFlags flags = ImGuiDragDropFlags_None) { return {flags}; }

    DragDropTarget_ DragDropTarget() { return {}; }

    Disabled_ Disabled(const bool disabled = true) { return {disabled}; }

    Group_ Group() { return {}; }

    /****************
     * TEXT HELPERS *
     ****************/

    void TextUnformatted(const std::string_view text) {
        ImGui::TextUnformatted(text.data(), text.data() + text.size());
    }

    template <typename... T>
    void Text(fmt::format_string<T...> fmt, T &&...args) {
        const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
        TextUnformatted(formatted);
    }

    template <typename... T>
    void TextColored(const ImVec4 &col, fmt::format_string<T...> fmt, T &&...args) {
        ImGui::PushStyleColor(ImGuiCol_Text, col);
        const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
        TextUnformatted(formatted);
        ImGui::PopStyleColor();
    }

    template <typename... T>
    void TextDisabled(fmt::format_string<T...> fmt, T &&...args) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
        const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
        TextUnformatted(formatted);
        ImGui::PopStyleColor();
    }

    template <typename... T>
    void TextWrapped(fmt::format_string<T...> fmt, T &&...args) {
        ImGui::PushTextWrapPos(0.0f);
        const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
        TextUnformatted(formatted);
        ImGui::PopTextWrapPos();
    }

    template <typename... T>
    void LabelText(const std::string &label, fmt::format_string<T...> fmt, T &&...args) {
        const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
        ImGui::LabelText(label.c_str(), formatted.c_str());
    }

    template <typename... T>
    void BulletText(fmt::format_string<T...> fmt, T &&...args) {
        ImGui::Bullet();
        const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
        TextUnformatted(formatted);
    }

    template <typename... T>
    void SeparatorText(fmt::format_string<T...> fmt, T &&...args) {
        const auto formatted = fmt::vformat(fmt, fmt::make_format_args(std::forward<T>(args)...));
        ImGui::SeparatorText(formatted.c_str());
    }
};
} // namespace theia
