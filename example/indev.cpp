#include "theia/theia.hpp"

int main(int, char *[]) {
    const auto glfw = glfwpp::Context();

    const auto monitor = glfwpp::get_primary_monitor();
    const auto window = glfwpp::WindowBuilder()
                            .context_version(4, 6)
                            .opengl_profile(GLFW_OPENGL_CORE_PROFILE)
                            .title("Indev")
                            .monitor(monitor->handle())
                            .match_vidmode(monitor->vidmode())
                            .build();
    window->set_icon("assets/gem_16x16.png");

    window->make_context_current();
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        throw std::runtime_error("Failed to initialize Glad");
    }
    THEIA_LOG_INFO("OpenGL Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

    glfwSetKeyCallback(window->handle(), [](GLFWwindow *window, int key, int, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            static_cast<glfwpp::Window *>(glfwGetWindowUserPointer(window))->set_should_close(true);
        }
    });

    while (!window->should_close()) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        window->swap_buffers();
    }
}
