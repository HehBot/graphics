#ifndef LINUXWINDOW_H
#define LINUXWINDOW_H

#include <cstdint>
#include <graphicscontext.h>
#include <window.h>

struct GLFWwindow;

class LinuxWindow : public Window {
public:
    LinuxWindow(std::shared_ptr<GraphicsContext> context, Window::Prop const& props);
    virtual ~LinuxWindow();

    virtual void set_event_callback(std::function<void(Event&)> const& callback) override { data.event_callback = callback; }

    virtual void on_update();

    virtual uint32_t get_width() const override { return data.width; }
    virtual uint32_t get_heigth() const override { return data.height; }

    virtual void set_vsync(bool enable) override;
    virtual bool is_vsync() const override { return data.vsync; }

    virtual void* get_native_handle() const override { return (void*)window_handle; }

private:
    std::shared_ptr<GraphicsContext> context;
    GLFWwindow* window_handle;

    struct Data {
        std::string title;
        uint32_t width, height;
        bool vsync;
        EventCallbackFn event_callback;
    } data;
};

#endif // LINUXWINDOW_H
