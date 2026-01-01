#include "theia/theia.hpp"

int main(int, char *[]) {
    const auto glfw = glfwpp::Context();

    glfwpp::set_monitor_callbacks();

    // const auto monitor =
    //     glfwpp::get_primary_monitor().or_else([] { return std::optional(glfwpp::get_monitors()[0]); }).value();
    const auto window = glfwpp::WindowBuilder()
                            .context_version(4, 6)
                            .opengl_profile(glfwpp::OpenGLProfile::Core)
                            .title("Indev")
                            .size(glm::ivec2{800, 600})
                            .wayland_app_id("theia")
                            // .monitor(monitor)
                            // .match_vidmode(monitor)
                            .build();
    window->set_icon("assets/gem_16x16.png");

    window->make_context_current();
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        throw std::runtime_error("Failed to initialize Glad");
    }
    THEIA_LOG_DEBUG("OpenGL Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

    const auto arrow = glfwpp::Cursor(glfwpp::CursorShape::Arrow);
    const auto resize_ew = glfwpp::Cursor(glfwpp::CursorShape::ResizeEW);
    const auto resize_ns = glfwpp::Cursor(glfwpp::CursorShape::ResizeNS);

    const auto hermes_id = theia::Hermes::instance().acquire_id();

    theia::Hermes::instance().subscribe<glfwpp::event::KeyEvent>(hermes_id, [&](auto *e) {
        switch (e->action) {
        case GLFW_PRESS:
            switch (e->key) {
            case GLFW_KEY_ESCAPE:
                e->window.set_should_close(true);
                break;
            case GLFW_KEY_1:
                e->window.set_cursor(arrow);
                break;
            case GLFW_KEY_2:
                e->window.set_cursor(resize_ew);
                break;
            case GLFW_KEY_3:
                e->window.set_cursor(resize_ns);
                break;
            default:;
            }
        default:;
        }
    });

    theia::Dear::Init(window->handle());

    while (!window->should_close()) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        auto &dear = theia::Dear::Instance();
        dear.NewFrame();
        dear.Begin("Hello, Dear ImGui!") && [&] {
            dear.Text("{:.2f} fps", ImGui::GetIO().Framerate);
            dear.Text("text, text, text");
        };
        dear.Render();

        window->swap_buffers();
    }

    theia::Dear::Shutdown();
}
