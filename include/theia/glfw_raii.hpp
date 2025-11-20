#pragma once

namespace theia {
class GlfwContext {
public:
    GlfwContext();
    ~GlfwContext();

    GlfwContext(const GlfwContext &other) = delete;
    GlfwContext(GlfwContext &&other) noexcept = delete;

    GlfwContext &operator=(const GlfwContext &other) = delete;
    GlfwContext &operator=(GlfwContext &&other) noexcept = delete;
};
} // namespace theia
