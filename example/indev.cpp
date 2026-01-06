#include "theia/theia.hpp"
#include <glad/gl.h>

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

    const auto dear = Dear::Context(*window);

    while (!window->should_close()) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Dear::NewFrame();
        Dear::Begin("Hello, Dear ImGui!") && [&] {
            Dear::Text("{:.2f} fps", ImGui::GetIO().Framerate);
            Dear::Text("text, text, text");
        };
        Dear::Render();

        window->swap_buffers();
        glfwPollEvents();
    }
}
