#ifndef WINDOW_H
#define WINDOW_H

#include <cstdint>
#include <memory>
#include <string>

class GraphicsContext;

class Window {
public:
    struct Prop {
        std::string title;
        uint32_t width;
        uint32_t height;

        Prop(std::string const& title = "graphics", uint32_t width = 800, uint32_t height = 600)
            : title(title), width(width), height(height)
        {
        }
    };

    virtual ~Window() = default;

    //         virtual void set_event_callback(EventCallbackFn const& callback) = 0;

    virtual void swap_buffers() = 0;

    virtual uint32_t get_width() const = 0;
    virtual uint32_t get_heigth() const = 0;

    virtual void set_vsync(bool enabled) = 0;
    virtual bool is_vsync() const = 0;

    virtual void* get_native_handle() const = 0;

    static std::unique_ptr<Window> create(std::shared_ptr<GraphicsContext> context, Window::Prop const& props = Window::Prop());
};

#endif // WINDOW_H
