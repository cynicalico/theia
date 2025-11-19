#include "theia/theia.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main(int, char *[]) {
    theia::Logger::init();

    glfwSetErrorCallback(
        [](int error, const char *description) { THEIA_LOG_ERROR("GLFW error {}: {}", error, description); });

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    auto window =
        theia::WindowBuilder().context_version(4, 6).opengl_profile(GLFW_OPENGL_CORE_PROFILE).title("Indev").build();
    window->make_context_current();

    if (gladLoadGL(glfwGetProcAddress) == 0) {
        throw std::runtime_error("Failed to initialize Glad");
    }

    THEIA_LOG_INFO("OpenGL Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

    while (!window->should_close()) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        window->swap_buffers();
    }

    glfwTerminate();
}
