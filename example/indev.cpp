#include "theia/theia.hpp"

int main(int, char *[]) {
    const auto glfw = glfwpp::Context();

    glfwpp::set_monitor_callbacks();

    const auto monitor = glfwpp::get_primary_monitor();
    const auto window = glfwpp::WindowBuilder()
                            .context_version(4, 6)
                            .opengl_profile(glfwpp::OpenGLProfile::Core)
                            .title("Indev")
                            .monitor(*monitor)
                            .match_vidmode(*monitor)
                            .build();
    window->set_icon("assets/gem_16x16.png");

    window->make_context_current();
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        throw std::runtime_error("Failed to initialize Glad");
    }
    THEIA_LOG_INFO("OpenGL Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

    const auto hermes_id = theia::Hermes::instance().get_id();

    theia::Hermes::instance().subscribe<glfwpp::event::KeyEvent>(hermes_id, [](auto *e) {
        if (e->action == GLFW_PRESS && e->key == GLFW_KEY_ESCAPE) e->window.set_should_close(true);
    });

    while (!window->should_close()) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        window->swap_buffers();
    }
}
