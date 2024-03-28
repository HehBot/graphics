#include <cassert>
#include <platform/opengl/renderer.h>
#include <renderer.h>
#include <window.h>

using namespace graphics;

Renderer::API Renderer::api = Renderer::API::OpenGL;

std::unique_ptr<Renderer> Renderer::create(Window const* window, std::initializer_list<Renderer::Option> opt)
{
    switch (api) {
    case Renderer::API::None:
        assert(false && "Renderer API not set");
    case Renderer::API::OpenGL:
        return std::make_unique<OpenGLRenderer>(window, opt);
    }
    assert(false && "Bad Renderer API");
}
