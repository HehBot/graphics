#include "linuxwindow.h"

#include <GLFW/glfw3.h>
#include <event.h>
#include <iostream>

static Button glfw_code_to_button(int code)
{
    static Button b[] = { Button::Left, Button::Right, Button::Middle, Button::B3, Button::B4, Button::B5, Button::B6, Button::Last };
    return b[code];
}
static Key glfw_code_to_key(int code)
{
    if (code == 256)
        return Key::Escape;
    else
        return Key::Unknown;
}

LinuxWindow::LinuxWindow(std::shared_ptr<GraphicsContext> context, Window::Prop const& props)
    : context(context), data { props.title, props.width, props.height, true, [](Event&) {} }
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    window_handle = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, (GLFWwindow*)context->get_native_handle());
    // TODO WHYYYYYYYYY
    glfwMakeContextCurrent(window_handle);

    glfwSetWindowUserPointer(window_handle, (void*)&data);
    glfwSetWindowSizeCallback(window_handle, [](GLFWwindow* window, int width, int height) {
        Data& data = *(Data*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.event_callback(event);
    });
    glfwSetWindowCloseCallback(window_handle, [](GLFWwindow* window) {
        Data& data = *(Data*)glfwGetWindowUserPointer(window);

        WindowCloseEvent event;
        data.event_callback(event);
    });
    glfwSetKeyCallback(window_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Data& data = *(Data*)glfwGetWindowUserPointer(window);
        switch (action) {
        case GLFW_PRESS: {
            KeyPressedEvent event(glfw_code_to_key(key));
            data.event_callback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(glfw_code_to_key(key));
            data.event_callback(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(glfw_code_to_key(key), true);
            data.event_callback(event);
            break;
        }
        }
    });
    glfwSetMouseButtonCallback(window_handle, [](GLFWwindow* window, int button, int action, int mods) {
        Data& data = *(Data*)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
            MouseButtonPressedEvent event(glfw_code_to_button(button));
            data.event_callback(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(glfw_code_to_button(button));
            data.event_callback(event);
            break;
        }
        }
    });

    glfwSetScrollCallback(window_handle, [](GLFWwindow* window, double x_off, double y_off) {
        Data& data = *(Data*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)x_off, (float)y_off);
        data.event_callback(event);
    });

    glfwSetCursorPosCallback(window_handle, [](GLFWwindow* window, double x, double y) {
        Data& data = *(Data*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)x, (float)y);
        data.event_callback(event);
    });
}
LinuxWindow::~LinuxWindow()
{
    glfwDestroyWindow(window_handle);
}

void LinuxWindow::on_update()
{
    glfwPollEvents();
    glfwSwapBuffers(window_handle);
}

void LinuxWindow::set_vsync(bool enable)
{
    if (enable && !data.vsync) {
        glfwSwapInterval(1);
        data.vsync = true;
    } else if (!enable && data.vsync) {
        glfwSwapInterval(0);
        data.vsync = false;
    }
}
