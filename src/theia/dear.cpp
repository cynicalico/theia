#include "theia/dear.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ImGuiContext *context_ = nullptr;

void theia::Dear::init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    context_ = ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL3_Init("#version 130");

    THEIA_LOG_DEBUG("Dear initialized, ImGui v{}", ImGui::GetVersion());
}

void theia::Dear::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(context_);
    context_ = nullptr;
}

theia::Dear &theia::Dear::instance() {
    static Dear instance_;
    if (!context_) throw std::runtime_error("Must call init before instance");
    return instance_;
}

void theia::Dear::new_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void theia::Dear::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool theia::Dear::want_capture_mouse() { return ImGui::GetIO().WantCaptureMouse; }

bool theia::Dear::want_capture_keyboard() { return ImGui::GetIO().WantCaptureKeyboard; }

void theia::Dear::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void theia::Dear::char_callback(GLFWwindow *window, unsigned int codepoint) {
    ImGui_ImplGlfw_CharCallback(window, codepoint);
}

void theia::Dear::cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
}

void theia::Dear::cursor_enter_callback(GLFWwindow *window, int entered) {
    ImGui_ImplGlfw_CursorEnterCallback(window, entered);
}

void theia::Dear::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void theia::Dear::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void theia::Dear::window_focus_callback(GLFWwindow *window, int focused) {
    ImGui_ImplGlfw_WindowFocusCallback(window, focused);
}

void theia::Dear::monitor_callback(GLFWmonitor *monitor, int event) { ImGui_ImplGlfw_MonitorCallback(monitor, event); }

theia::Dear::Begin theia::Dear::begin(const std::string_view title, bool *open, const ImGuiWindowFlags flags) {
    return Begin(title, open, flags);
}
