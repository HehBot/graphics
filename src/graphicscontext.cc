#include <graphicscontext.h>
#include <memory>
#include <platform/linux/graphicscontext.h>

std::shared_ptr<GraphicsContext> GraphicsContext::create()
{
    return std::make_shared<LinuxGraphicsContext>();
}
