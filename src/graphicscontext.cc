#include <graphicscontext.h>
#include <memory>
#include <platform/openglgraphicscontext.h>

std::shared_ptr<GraphicsContext> GraphicsContext::create()
{
    return std::make_shared<OpenGLGraphicsContext>();
}
