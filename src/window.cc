#include <memory>
#include <platform/linux/window.h>

Window const* Window::current = nullptr;

class GraphicsContext;

std::unique_ptr<Window> Window::create(std::shared_ptr<GraphicsContext> context, Window::Prop const& props)
{
    return std::make_unique<LinuxWindow>(context, props);
}
