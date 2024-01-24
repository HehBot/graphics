#include <memory>
#include <platform/opengl/shader.h>
#include <renderer.h>
#include <shader.h>

Shader const* Shader::current = nullptr;

std::shared_ptr<Shader> Shader::create(std::initializer_list<std::string> shaderpaths)
{
    switch (Renderer::get_api()) {
    case Renderer::API::None:
        assert(false && "Renderer API not set");
    case Renderer::API::OpenGL:
        return std::make_shared<OpenGLShader>(shaderpaths);
    }
    assert(false && "Bad Renderer API");
}
