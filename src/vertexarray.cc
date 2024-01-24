#include <memory>
#include <platform/opengl/vertexarray.h>
#include <renderer.h>
#include <vertexarray.h>

VertexArray const* VertexArray::current = nullptr;

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
