#ifndef WINDOW_H
#define WINDOW_H

#include <context.h>
#include <cstdint>
#include <event.h>
#include <functional>
#include <memory>
#include <string>
#include <util/scopedbind.h>

namespace graphics {
class Window {
public:
    struct Prop {
        std::string title;
        uint32_t width;
        uint32_t height;
    };

    virtual ~Window() = default;

    virtual void set_event_callback(std::function<void(Event&)> const& callback) = 0;

    virtual void bind() const = 0;

    virtual void on_update() = 0;

    virtual uint32_t get_width() const = 0;
    virtual uint32_t get_height() const = 0;

    virtual void set_vsync(bool enabled) = 0;
    virtual bool is_vsync() const = 0;

    virtual void* get_native_handle() const = 0;

    static std::unique_ptr<Window> create(std::shared_ptr<Context> context, Window::Prop const& props = { "graphics", 800, 600 });

protected:
    static Window const* current;
    friend class ScopedBind<Window>;
};
}

#endif // WINDOW_H
