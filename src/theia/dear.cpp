#include "theia/dear.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ImGuiContext *context_ = nullptr;

void theia::Dear::Init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    context_ = ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    if (!ImGui_ImplGlfw_InitForOpenGL(window, false))
        throw std::runtime_error("Failed to initialize ImGui GLFW backend");

    if (!ImGui_ImplOpenGL3_Init("#version 130")) throw std::runtime_error("Failed to initialize ImGui OpenGL backend");

    THEIA_LOG_DEBUG("Dear initialized, ImGui v{}", ImGui::GetVersion());
}

void theia::Dear::Shutdown() {
    if (context_) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext(context_);
        context_ = nullptr;
    }
}

theia::Dear &theia::Dear::Instance() {
    static Dear instance_;
    if (!context_) throw std::runtime_error("Must call init before instance");
    return instance_;
}

void theia::Dear::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void theia::Dear::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool theia::Dear::WantCaptureMouse() { return ImGui::GetIO().WantCaptureMouse; }

bool theia::Dear::WantCaptureKeyboard() { return ImGui::GetIO().WantCaptureKeyboard; }

void theia::Dear::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void theia::Dear::CharCallback(GLFWwindow *window, unsigned int codepoint) {
    ImGui_ImplGlfw_CharCallback(window, codepoint);
}

void theia::Dear::CursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
}

void theia::Dear::CursorEnterCallback(GLFWwindow *window, int entered) {
    ImGui_ImplGlfw_CursorEnterCallback(window, entered);
}

void theia::Dear::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void theia::Dear::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void theia::Dear::WindowFocusCallback(GLFWwindow *window, int focused) {
    ImGui_ImplGlfw_WindowFocusCallback(window, focused);
}

void theia::Dear::MonitorCallback(GLFWmonitor *monitor, int event) { ImGui_ImplGlfw_MonitorCallback(monitor, event); }
