#pragma once

#include "theia/hermes.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <optional>
#include <vector>

namespace glfwpp {
class Monitor {
public:
    explicit Monitor(GLFWmonitor *handle);

    const GLFWvidmode *vidmode() const;
    glm::ivec2 size() const;
    int w() const;
    int h() const;
    int red_bits() const;
    int green_bits() const;
    int blue_bits() const;
    int refresh_rate() const;

    [[nodiscard]] glm::ivec2 physical_size_mm() const;

    [[nodiscard]] glm::vec2 content_scale() const;

    [[nodiscard]] glm::ivec2 position() const;

    [[nodiscard]] glm::ivec4 work_area() const;

    const char *name() const;

    void *user_pointer() const;
    void set_user_pointer(void *ptr);

    const GLFWgammaramp *gamma_ramp() const;
    void set_gamma_ramp(const GLFWgammaramp &ramp) const;
    void set_gamma(float gamma) const;

    GLFWmonitor *handle() const;

private:
    GLFWmonitor *handle_{nullptr};
};

std::optional<Monitor> get_primary_monitor();
std::vector<Monitor> get_monitors();

namespace event {
enum class MonitorEventType {
    Connected = GLFW_CONNECTED,
    Disconnected = GLFW_DISCONNECTED,
};

struct MonitorEvent {
    MAKE_HERMES_ID(glfwpp::event::MonitorEvent);
    Monitor monitor;
    MonitorEventType event;
};
} // namespace event

void set_monitor_callbacks();
} // namespace glfwpp