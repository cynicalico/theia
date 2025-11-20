#include "theia/glfw_raii.hpp"
#include "theia/logger.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

theia::GlfwContext::GlfwContext() {
    glfwSetErrorCallback(
        [](int error, const char *description) { THEIA_LOG_ERROR("GLFW error {}: {}", error, description); });

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    THEIA_LOG_INFO("GLFW v{}", glfwGetVersionString());
}

theia::GlfwContext::~GlfwContext() { glfwTerminate(); }

theia::Monitor::Monitor(GLFWmonitor *handle)
    : handle_(handle) {}

const GLFWvidmode *theia::Monitor::vidmode() const { return glfwGetVideoMode(handle_); }

glm::ivec2 theia::Monitor::size() const {
    const auto *vm = vidmode();
    return vm ? glm::ivec2{vm->width, vm->height} : glm::ivec2{0};
}

int theia::Monitor::w() const {
    const auto *vm = vidmode();
    return vm ? vm->width : 0;
}

int theia::Monitor::h() const {
    const auto *vm = vidmode();
    return vm ? vm->height : 0;
}

int theia::Monitor::red_bits() const {
    const auto *vm = vidmode();
    return vm ? vm->redBits : 0;
}

int theia::Monitor::green_bits() const {
    const auto *vm = vidmode();
    return vm ? vm->greenBits : 0;
}

int theia::Monitor::blue_bits() const {
    const auto *vm = vidmode();
    return vm ? vm->blueBits : 0;
}

int theia::Monitor::refresh_rate() const {
    const auto *vm = vidmode();
    return vm ? vm->refreshRate : 0;
}

glm::ivec2 theia::Monitor::physical_size_mm() const {
    int width_mm, height_mm;
    glfwGetMonitorPhysicalSize(handle_, &width_mm, &height_mm);
    return {width_mm, height_mm};
}

glm::vec2 theia::Monitor::content_scale() const {
    float xscale, yscale;
    glfwGetMonitorContentScale(handle_, &xscale, &yscale);
    return {xscale, yscale};
}

glm::ivec2 theia::Monitor::position() const {
    int x, y;
    glfwGetMonitorPos(handle_, &x, &y);
    return {x, y};
}

glm::ivec4 theia::Monitor::work_area() const {
    int x, y, w, h;
    glfwGetMonitorWorkarea(handle_, &x, &y, &w, &h);
    return {x, y, w, h};
}

const char *theia::Monitor::name() const { return glfwGetMonitorName(handle_); }

void *theia::Monitor::user_pointer() const { return glfwGetMonitorUserPointer(handle_); }

void theia::Monitor::set_user_pointer(void *ptr) { glfwSetMonitorUserPointer(handle_, ptr); }

const GLFWgammaramp *theia::Monitor::gamma_ramp() const { return glfwGetGammaRamp(handle_); }

void theia::Monitor::set_gamma_ramp(const GLFWgammaramp &ramp) const { glfwSetGammaRamp(handle_, &ramp); }

GLFWmonitor *theia::Monitor::handle() const { return handle_; }

std::optional<theia::Monitor> theia::get_primary_monitor() {
    GLFWmonitor *mon = glfwGetPrimaryMonitor();
    if (!mon) return std::nullopt;
    return Monitor{mon};
}

std::vector<theia::Monitor> theia::get_monitors() {
    int count = 0;
    GLFWmonitor **list = glfwGetMonitors(&count);
    if (!list || count <= 0) return {};

    std::vector<Monitor> result;
    result.reserve(static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        result.emplace_back(list[i]);
    }
    return result;
}
