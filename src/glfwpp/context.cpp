#include "glfwpp/context.hpp"
#include "theia/logger.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

glfwpp::Context::Context() {
    glfwSetErrorCallback(
        [](int error, const char *description) { THEIA_LOG_ERROR("GLFW error {}: {}", error, description); });

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    THEIA_LOG_INFO("GLFW v{}", glfwGetVersionString());
}

glfwpp::Context::~Context() { glfwTerminate(); }
