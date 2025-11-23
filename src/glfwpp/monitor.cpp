#include "glfwpp/monitor.hpp"

glfwpp::Monitor::Monitor(GLFWmonitor *handle)
    : handle_(handle) {}

const GLFWvidmode *glfwpp::Monitor::vidmode() const { return glfwGetVideoMode(handle_); }

glm::ivec2 glfwpp::Monitor::size() const {
    const auto *vm = vidmode();
    return vm ? glm::ivec2{vm->width, vm->height} : glm::ivec2{0};
}

int glfwpp::Monitor::w() const {
    const auto *vm = vidmode();
    return vm ? vm->width : 0;
}

int glfwpp::Monitor::h() const {
    const auto *vm = vidmode();
    return vm ? vm->height : 0;
}

int glfwpp::Monitor::red_bits() const {
    const auto *vm = vidmode();
    return vm ? vm->redBits : 0;
}

int glfwpp::Monitor::green_bits() const {
    const auto *vm = vidmode();
    return vm ? vm->greenBits : 0;
}

int glfwpp::Monitor::blue_bits() const {
    const auto *vm = vidmode();
    return vm ? vm->blueBits : 0;
}

int glfwpp::Monitor::refresh_rate() const {
    const auto *vm = vidmode();
    return vm ? vm->refreshRate : 0;
}

glm::ivec2 glfwpp::Monitor::physical_size_mm() const {
    int width_mm, height_mm;
    glfwGetMonitorPhysicalSize(handle_, &width_mm, &height_mm);
    return {width_mm, height_mm};
}

glm::vec2 glfwpp::Monitor::content_scale() const {
    float xscale, yscale;
    glfwGetMonitorContentScale(handle_, &xscale, &yscale);
    return {xscale, yscale};
}

glm::ivec2 glfwpp::Monitor::position() const {
    int x, y;
    glfwGetMonitorPos(handle_, &x, &y);
    return {x, y};
}

glm::ivec4 glfwpp::Monitor::work_area() const {
    int x, y, w, h;
    glfwGetMonitorWorkarea(handle_, &x, &y, &w, &h);
    return {x, y, w, h};
}

const char *glfwpp::Monitor::name() const { return glfwGetMonitorName(handle_); }

void *glfwpp::Monitor::user_pointer() const { return glfwGetMonitorUserPointer(handle_); }

void glfwpp::Monitor::set_user_pointer(void *ptr) { glfwSetMonitorUserPointer(handle_, ptr); }

const GLFWgammaramp *glfwpp::Monitor::gamma_ramp() const { return glfwGetGammaRamp(handle_); }

void glfwpp::Monitor::set_gamma_ramp(const GLFWgammaramp &ramp) const { glfwSetGammaRamp(handle_, &ramp); }

void glfwpp::Monitor::set_gamma(float gamma) const { glfwSetGamma(handle_, gamma); }

GLFWmonitor *glfwpp::Monitor::handle() const { return handle_; }

std::optional<glfwpp::Monitor> glfwpp::get_primary_monitor() {
    GLFWmonitor *mon = glfwGetPrimaryMonitor();
    if (!mon) return std::nullopt;
    return Monitor{mon};
}

std::vector<glfwpp::Monitor> glfwpp::get_monitors() {
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

void glfwpp::set_monitor_callbacks() {
    glfwSetMonitorCallback([](GLFWmonitor *monitor, int event) {
        theia::Hermes::instance().publish<event::MonitorEvent>(Monitor(monitor),
                                                               static_cast<event::MonitorEventType>(event));
    });
}
