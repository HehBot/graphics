#include <buffer.h>
#include <memory>
#include <platform/openglbuffer.h>
#include <renderer.h>

std::shared_ptr<VertexBuffer> VertexBuffer::create(uint32_t size)
{
    switch (Renderer::get_api()) {
    case Renderer::API::None:
        assert(false && "Renderer API not set");
    case Renderer::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(size);
    }
    assert(false && "Bad Renderer API");
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
{
    switch (Renderer::get_api()) {
    case Renderer::API::None:
        assert(false && "Renderer API not set");
    case Renderer::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    }
    assert(false && "Bad Renderer API");
}

std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t count)
{
    switch (Renderer::get_api()) {
    case Renderer::API::None:
        assert(false && "Renderer API not set");
    case Renderer::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(indices, count);
    }
    assert(false && "Bad Renderer API");
}
