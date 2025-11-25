#include "glfwpp/cursor.hpp"

#include "theia/io.hpp"

glfwpp::Cursor::Cursor(GLFWcursor *handle)
    : handle_(handle) {}

glfwpp::Cursor::Cursor(CursorShape shape)
    : handle_(glfwCreateStandardCursor(static_cast<int>(shape))) {}

glfwpp::Cursor::Cursor(const std::filesystem::path &path, int xhot, int yhot) {
    auto [bytes, w, h] = theia::read_image_bytes(path);
    auto image = GLFWimage{w, h, reinterpret_cast<unsigned char *>(bytes.data())};
    handle_ = glfwCreateCursor(&image, xhot, yhot);
}

glfwpp::Cursor::~Cursor() {
    if (handle_) glfwDestroyCursor(handle_);
}

glfwpp::Cursor::Cursor(Cursor &&other) noexcept
    : handle_(other.handle_) {
    other.handle_ = nullptr;
}

glfwpp::Cursor &glfwpp::Cursor::operator=(Cursor &&other) noexcept {
    if (this != &other) {
        if (handle_) glfwDestroyCursor(handle_);
        handle_ = other.handle_;
        other.handle_ = nullptr;
    }
    return *this;
}

GLFWcursor *glfwpp::Cursor::handle() const { return handle_; }
