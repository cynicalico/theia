#include "theia/theia.hpp"

int main(int, char *[]) {
    using theia::Dear;

    const auto glfw = glfwpp::Context();

    const auto window = glfwpp::WindowBuilder()
                            .context_version(4, 6)
                            .opengl_profile(glfwpp::OpenGLProfile::Core)
                            .title("Indev")
                            .size(glm::ivec2{800, 600})
                            .wayland_app_id("theia")
                            .build();
    window->set_icon("assets/gem_16x16.png");

    window->make_context_current();
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        throw std::runtime_error("Failed to initialize Glad");
    }
    THEIA_LOG_DEBUG("OpenGL Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

    const auto dear = Dear::Context(*window);

    while (!window->should_close()) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        Dear::NewFrame();
        Dear::Begin("Hello, Dear ImGui!") && [&] {
            Dear::Text("{:.2f} fps", ImGui::GetIO().Framerate);
            Dear::Text("text, text, text");
        };
        Dear::Render();

        window->swap_buffers();
    }
}
