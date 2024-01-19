#include <memory>
#include <platform/openglvertexarray.h>
#include <renderer.h>
#include <vertexarray.h>

std::shared_ptr<VertexArray> VertexArray::create()
{
    switch (Renderer::get_api()) {
    case Renderer::API::None:
        assert(false && "Renderer API not set");
    case Renderer::API::OpenGL:
        return std::make_shared<OpenGLVertexArray>();
    }
    assert(false && "Bad Renderer API");
}
