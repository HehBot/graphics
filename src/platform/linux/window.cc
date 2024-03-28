#include "window.h"

#include <GLFW/glfw3.h>
#include <event.h>
#include <util/scopedbind.h>

using namespace graphics;

static Button glfw_code_to_button(int code)
{
    static Button b[] = { Button::Left, Button::Right, Button::Middle, Button::B3, Button::B4, Button::B5, Button::B6, Button::Last };
    return b[code];
}
static Key glfw_code_to_key(int code)
{
#define helper(X)            \
    {                        \
        GLFW_KEY_##X, Key::X \
    }
#define helper_digit(X)         \
    {                           \
        GLFW_KEY_##X, Key::D##X \
    }
    static std::unordered_map<int, Key> const convert = {
        helper(SPACE),
        helper(APOSTROPHE),
        helper(COMMA),
        helper(MINUS),
        helper(PERIOD),
        helper(SLASH),
        helper_digit(0),
        helper_digit(1),
        helper_digit(2),
        helper_digit(3),
        helper_digit(4),
        helper_digit(5),
        helper_digit(6),
        helper_digit(7),
        helper_digit(8),
        helper_digit(9),
        helper(SEMICOLON),
        helper(EQUAL),
        helper(A),
        helper(B),
        helper(C),
        helper(D),
        helper(E),
        helper(F),
        helper(G),
        helper(H),
        helper(I),
        helper(J),
        helper(K),
        helper(L),
        helper(M),
        helper(N),
        helper(O),
        helper(P),
        helper(Q),
        helper(R),
        helper(S),
        helper(T),
        helper(U),
        helper(V),
        helper(W),
        helper(X),
        helper(Y),
        helper(Z),
        helper(LEFT_BRACKET),
        helper(BACKSLASH),
        helper(RIGHT_BRACKET),
        helper(GRAVE_ACCENT),
        helper(ESCAPE),
        helper(ENTER),
        helper(TAB),
        helper(BACKSPACE),
        helper(INSERT),
        helper(DELETE),
        helper(RIGHT),
        helper(LEFT),
        helper(DOWN),
        helper(UP),
        helper(PAGE_UP),
        helper(PAGE_DOWN),
        helper(HOME),
        helper(END),
        helper(CAPS_LOCK),
        helper(SCROLL_LOCK),
        helper(NUM_LOCK),
        helper(PRINT_SCREEN),
        helper(PAUSE),
        helper(F1),
        helper(F2),
        helper(F3),
        helper(F4),
        helper(F5),
        helper(F6),
        helper(F7),
        helper(F8),
        helper(F9),
        helper(F10),
        helper(F11),
        helper(F12),
        helper(F13),
        helper(F14),
        helper(F15),
        helper(F16),
        helper(F17),
        helper(F18),
        helper(F19),
        helper(F20),
        helper(F21),
        helper(F22),
        helper(F23),
        helper(F24),
        helper(F25),
        helper(KP_0),
        helper(KP_1),
        helper(KP_2),
        helper(KP_3),
        helper(KP_4),
        helper(KP_5),
        helper(KP_6),
        helper(KP_7),
        helper(KP_8),
        helper(KP_9),
        helper(KP_DECIMAL),
        helper(KP_DIVIDE),
        helper(KP_MULTIPLY),
        helper(KP_SUBTRACT),
        helper(KP_ADD),
        helper(KP_ENTER),
        helper(KP_EQUAL),
        helper(LEFT_SHIFT),
        helper(LEFT_CONTROL),
        helper(LEFT_ALT),
        helper(LEFT_SUPER),
        helper(RIGHT_SHIFT),
        helper(RIGHT_CONTROL),
        helper(RIGHT_ALT),
        helper(RIGHT_SUPER),
        helper(MENU),
    };
#undef helper
#undef helper_digit
    auto const ite = convert.end();
    auto it = convert.find(code);
    if (it == ite)
        return Key::UNKNOWN;
    return it->second;
}

LinuxWindow::LinuxWindow(std::shared_ptr<Context> context, Window::Prop const& props)
    : context(context), data { props.title, props.width, props.height, true, [](Event&) {} }
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    window_handle = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, (GLFWwindow*)context->get_native_handle());

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
    if (current == this)
        current = nullptr;
    glfwDestroyWindow(window_handle);
}

void LinuxWindow::bind() const
{
    if (current != this) {
        current = this;
        glfwMakeContextCurrent(window_handle);
    }
}

void LinuxWindow::on_update()
{
    glfwPollEvents();
    glfwSwapBuffers(window_handle);
}

void LinuxWindow::set_vsync(bool enable)
{
    ScopedBind<Window> scoped_bind(this);
    if (enable && !data.vsync) {
        glfwSwapInterval(1);
        data.vsync = true;
    } else if (!enable && data.vsync) {
        glfwSwapInterval(0);
        data.vsync = false;
    }
}
