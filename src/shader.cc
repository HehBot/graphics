#include <memory>
#include <platform/openglshader.h>
#include <renderer.h>
#include <shader.h>

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
