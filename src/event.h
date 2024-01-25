#ifndef EVENT_H
#define EVENT_H

namespace graphics {
enum class EventType {
    WindowClose,
    WindowResize,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

#define EVENT_TYPE(type)        \
    EventType get_type() const  \
    {                           \
        return EventType::type; \
    }

class Event {
public:
    virtual ~Event() = default;

    virtual EventType get_type() const = 0;

    bool handled = false;
};

class WindowCloseEvent : public Event {
public:
    EVENT_TYPE(WindowClose)
};

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t width, uint32_t height)
        : width(width), height(height)
    {
    }

    uint32_t get_width() const { return width; }
    uint32_t get_height() const { return height; }

    EVENT_TYPE(WindowResize)

private:
    uint32_t const width, height;
};

enum class Key {
    Unknown,
    Space,
    Apostrophe,
    Comma,
    Minus,
    Period,
    Slash,
    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,
    D8,
    D9,
    Semicolon,
    Equal,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    LeftBracket,
    Backslash,
    RightBracket,
    Tilde,
    Escape,
    Enter,
    Tab,
    Backspace,
    Insert,
    Delete,
    Right,
    Left,
    Down,
    Up,
    PageUp,
    PageDown,
    Home,
    End,
    CapsLock,
    ScrollLock,
    NumLock,
    PrintScreen,
    Pause,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,
    KP0,
    KP1,
    KP2,
    KP3,
    KP4,
    KP5,
    KP6,
    KP7,
    KP8,
    KP9,
    KPDecimal,
    KPDivide,
    KPMultiply,
    KPSubtract,
    KPAdd,
    KPEnter,
    KPEqual,
    LeftShift,
    LeftControl,
    LeftAlt,
    LeftSuper,
    RightShift,
    RightControl,
    RightAlt,
    RightSuper,
    Menu
};

class KeyEvent : public Event {
public:
    Key get_key() const { return key; }

protected:
    KeyEvent(Key key)
        : key(key)
    {
    }

    Key key;
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(Key key, bool repeated = false)
        : KeyEvent(key), repeated(repeated)
    {
    }

    EVENT_TYPE(KeyPressed)

private:
    bool repeated;
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(Key key)
        : KeyEvent(key)
    {
    }

    EVENT_TYPE(KeyReleased)
};

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y)
        : x(x), y(y)
    {
    }

    float get_x() { return x; }
    float get_y() { return y; }

    EVENT_TYPE(MouseMoved)

private:
    float const x, y;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float x_off, float y_off)
        : x_off(x_off), y_off(y_off)
    {
    }

    float get_x_off() { return x_off; }
    float get_y_off() { return y_off; }

    EVENT_TYPE(MouseScrolled)

private:
    float const x_off, y_off;
};

enum class Button {
    Left,
    Right,
    Middle,
    B3,
    B4,
    B5,
    B6,
    Last
};

class MouseButtonEvent : public Event {
public:
    Button get_button() { return button; }

protected:
    MouseButtonEvent(Button button)
        : button(button)
    {
    }

    Button button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(Button button)
        : MouseButtonEvent(button)
    {
    }

    EVENT_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(Button button)
        : MouseButtonEvent(button)
    {
    }

    EVENT_TYPE(MouseButtonReleased)
};
}

#endif // EVENT_H
