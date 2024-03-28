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

    uint32_t const& width;
    uint32_t const& height;

    virtual void set_vsync(bool enabled) = 0;
    virtual bool is_vsync() const = 0;

    virtual void* get_native_handle() const = 0;

    virtual double get_time() const = 0;
    virtual void init_delta_timer() = 0;
    virtual double get_delta_time() = 0;

    static std::unique_ptr<Window> create(std::shared_ptr<Context> context, Window::Prop const& props = { "graphics", 800, 600 });

protected:
    static Window const* current;
    Window(uint32_t const& w, uint32_t const& h)
        : width(w), height(h) { }
    friend class ScopedBind<Window>;
};
}

#endif // WINDOW_H
