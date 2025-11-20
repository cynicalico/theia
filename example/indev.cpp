#include "theia/theia.hpp"

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main(int, char *[]) {
    const auto glfw = theia::GlfwContext();

    const auto window = theia::WindowBuilder()
                            .context_version(4, 6)
                            .opengl_profile(GLFW_OPENGL_CORE_PROFILE)
                            .title("Indev")
                            .visible(false)
                            .build();

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
}
