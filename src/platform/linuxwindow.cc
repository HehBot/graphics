#include "linuxwindow.h"

#include <GLFW/glfw3.h>

LinuxWindow::LinuxWindow(std::shared_ptr<GraphicsContext> context, Window::Prop const& props)
    : width(props.width), height(props.height), vsync(true)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    window_handle = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, (GLFWwindow*)context->get_native_handle());

    // TODO WHYYYYYYYYY
    glfwMakeContextCurrent(window_handle);
}

void LinuxWindow::swap_buffers()
{
    glfwSwapBuffers(window_handle);
}

void LinuxWindow::set_vsync(bool enable)
{
    if (enable && !vsync) {
        glfwSwapInterval(1);
        vsync = true;
    } else if (!enable && vsync) {
        glfwSwapInterval(0);
        vsync = false;
    }
}
