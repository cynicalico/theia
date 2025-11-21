#pragma once

namespace glfwpp {
class Context {
public:
    Context();
    ~Context();

    Context(const Context &other) = delete;
    Context(Context &&other) = delete;

    Context &operator=(const Context &other) = delete;
    Context &operator=(Context &&other) = delete;
};
} // namespace glfwpp
