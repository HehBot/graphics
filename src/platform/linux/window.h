#ifndef PLATFORM_LINUX_WINDOW_H
#define PLATFORM_LINUX_WINDOW_H

#include <context.h>
#include <cstdint>
#include <window.h>

struct GLFWwindow;

class LinuxWindow : public graphics::Window {
public:
    LinuxWindow(std::shared_ptr<graphics::Context> context, graphics::Window::Prop const& props);
    virtual ~LinuxWindow();

    virtual void set_event_callback(std::function<void(graphics::Event&)> const& callback) override { data.event_callback = callback; }

    virtual void bind() const;

    virtual void on_update();

    virtual uint32_t get_width() const override { return data.width; }
    virtual uint32_t get_height() const override { return data.height; }

    virtual void set_vsync(bool enable) override;
    virtual bool is_vsync() const override { return data.vsync; }

    virtual void* get_native_handle() const override { return (void*)window_handle; }

private:
    std::shared_ptr<graphics::Context> context;
    GLFWwindow* window_handle;

    struct Data {
        std::string title;
        uint32_t width, height;
        bool vsync;
        std::function<void(graphics::Event&)> event_callback;
    } data;
};

#endif // PLATFORM_LINUX_WINDOW_H
