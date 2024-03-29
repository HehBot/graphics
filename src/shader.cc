#include <memory>
#include <platform/opengl/shader.h>
#include <renderer.h>
#include <shader.h>

using namespace graphics;

Shader const* Shader::current = nullptr;

std::shared_ptr<Shader> Shader::load(std::initializer_list<std::string> shader_paths)
{
    switch (Renderer::get_api()) {
    case Renderer::API::None:
        assert(false && "Renderer API not set");
    case Renderer::API::OpenGL:
        return std::make_shared<OpenGLShader>(shader_paths);
    }
    assert(false && "Bad Renderer API");
}
