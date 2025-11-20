#include "theia/glfw_raii.hpp"
#include "theia/logger.hpp"

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
