#include <context.h>
#include <memory>
#include <platform/linux/window.h>

using namespace graphics;

Window const* Window::current = nullptr;

std::unique_ptr<Window> Window::create(std::shared_ptr<Context> context, Window::Prop const& props)
{
    return std::make_unique<LinuxWindow>(context, props);
}
