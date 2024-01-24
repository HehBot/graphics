#include <cassert>
#include <memory>
#include <platform/opengl/texture.h>
#include <renderer.h>
#include <texture.h>

std::shared_ptr<Texture2D> Texture2D::create(Texture::Spec const& spec)
{
    switch (Renderer::get_api()) {
    case Renderer::API::None:
        assert(false && "Renderer API not set");
    case Renderer::API::OpenGL:
        return std::make_shared<OpenGLTexture2D>(spec);
    }
    assert(false && "Bad Renderer API");
}
