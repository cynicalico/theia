#include "theia/theia.hpp"

int main(int, char *[]) {
    const auto glfw = theia::GlfwContext();

    const auto monitors = theia::get_monitors();
    const auto window = theia::WindowBuilder()
                            .context_version(4, 6)
                            .opengl_profile(GLFW_OPENGL_CORE_PROFILE)
                            .title("Indev")
                            // .monitor(monitors[1].handle())
                            .match_vidmode(monitors[0].vidmode())
                            .position(monitors[0].position())
                            .decorated(false)
                            .build();

    window->set_icon("assets/gem_16x16.png");

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
