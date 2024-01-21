#ifndef LINUXWINDOW_H
#define LINUXWINDOW_H

#include <cstdint>
#include <graphicscontext.h>
#include <window.h>

struct GLFWwindow;

class LinuxWindow : public Window {
public:
    LinuxWindow(std::shared_ptr<GraphicsContext> context, Window::Prop const& props);
    virtual ~LinuxWindow() { }

    //         virtual void set_event_callback(EventCallbackFn const& callback) override;

    virtual void swap_buffers();

    virtual uint32_t get_width() const override { return width; }
    virtual uint32_t get_heigth() const override { return height; }

    virtual void set_vsync(bool enable) override;
    virtual bool is_vsync() const override { return vsync; }

    virtual void* get_native_handle() const override { return (void*)window_handle; }

private:
    GLFWwindow* window_handle;
    uint32_t width, height;
    bool vsync;
};

#endif // LINUXWINDOW_H
