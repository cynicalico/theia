#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <filesystem>

namespace glfwpp {
enum class CursorShape {
    Arrow = GLFW_ARROW_CURSOR,
    IBeam = GLFW_IBEAM_CURSOR,
    Crosshair = GLFW_CROSSHAIR_CURSOR,
    PointingHand = GLFW_POINTING_HAND_CURSOR,
    ResizeEW = GLFW_RESIZE_EW_CURSOR,
    ResizeNS = GLFW_RESIZE_NS_CURSOR,
    ResizeNWSE = GLFW_RESIZE_NWSE_CURSOR,
    ResizeNESW = GLFW_RESIZE_NESW_CURSOR,
    ResizeAll = GLFW_RESIZE_ALL_CURSOR,
    NotAllowed = GLFW_NOT_ALLOWED_CURSOR,
};

class Cursor {
public:
    Cursor(GLFWcursor *handle);
    Cursor(CursorShape shape);
    Cursor(const std::filesystem::path &path, int xhot, int yhot);

    ~Cursor();

    Cursor(const Cursor &other) = delete;
    Cursor &operator=(const Cursor &other) = delete;

    Cursor(Cursor &&other) noexcept;
    Cursor &operator=(Cursor &&other) noexcept;

    GLFWcursor *handle() const;

private:
    GLFWcursor *handle_;
};
} // namespace glfwpp