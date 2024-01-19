#include <cassert>
#include <platform/openglrenderer.h>
#include <renderer.h>

Renderer::API Renderer::api = Renderer::API::OpenGL;

std::unique_ptr<Renderer> Renderer::create()
{
    switch (api) {
    case Renderer::API::None:
        assert(false && "Renderer API not set");
    case Renderer::API::OpenGL:
        return std::make_unique<OpenGLRenderer>();
    }
    assert(false && "Bad Renderer API");
}
