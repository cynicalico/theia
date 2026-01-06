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

    const auto hermes_id = theia::Hermes::instance().acquire_id();
    theia::Hermes::instance().subscribe<theia::OverlayTabEvent>(hermes_id, [&](const auto *) {
        Dear::TabItem("Window") && [&] {
            static bool vsync = true;
            if (ImGui::Checkbox("vsync", &vsync)) {
                if (vsync) {
                    glfwSwapInterval(1);
                } else {
                    glfwSwapInterval(0);
                }
            }

            // TODO: Size
            // TODO: Size limits
            // TODO: Aspect ratio
            // TODO: Position

            static char title_buf[1024];
            const auto title = window->title();
            std::memcpy(title_buf, title, std::strlen(title));
            if (ImGui::InputText("title", title_buf, 1024)) {
                window->set_title(title_buf);
            }

            bool resizable = window->resizable();
            if (ImGui::Checkbox("resizable", &resizable)) {
                window->set_resizable(resizable);
            }

            bool decorated = window->decorated();
            if (ImGui::Checkbox("decorated", &decorated)) {
                window->set_decorated(decorated);
            }

            bool auto_iconify = window->auto_iconify();
            if (ImGui::Checkbox("auto iconify", &auto_iconify)) {
                window->set_auto_iconify(auto_iconify);
            }

            bool floating = window->floating();
            if (ImGui::Checkbox("floating", &floating)) {
                window->set_floating(floating);
            }

            bool focus_on_show = window->focused_on_show();
            if (ImGui::Checkbox("focus on show", &focus_on_show)) {
                window->set_focus_on_show(focus_on_show);
            }

            bool mouse_passthrough = window->mouse_passthrough();
            if (ImGui::Checkbox("mouse passthrough", &mouse_passthrough)) {
                window->set_mouse_passthrough(mouse_passthrough);
            }

            float opacity = window->opacity();
            if (ImGui::SliderFloat("opacity", &opacity, 0.0f, 1.0f)) {
                window->set_opacity(opacity);
            }
        };
    });

    const auto dear = Dear::Context(*window);

    while (!window->should_close()) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Dear::NewFrame();
        theia::draw_overlay();
        Dear::Render();

        window->swap_buffers();
    }
}
