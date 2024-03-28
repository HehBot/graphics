#include <cassert>
#include <memory>
#include <platform/opengl/texture.h>
#include <renderer.h>
#include <texture.h>
#include <util/stb_image/stb_image.h>

using namespace graphics;

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

bool Texture2D::stbi_inited = false;
std::shared_ptr<Texture2D> Texture2D::create(char const* path)
{
    if (!stbi_inited) {
        stbi_set_flip_vertically_on_load(true);
        stbi_inited = true;
    }

    int width, height, channels;
    stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);
    std::shared_ptr<Texture2D> tex = Texture2D::create({ (uint32_t)width, (uint32_t)height, (channels == 4 ? ImageFormat::RGBA8 : ImageFormat::RGB8), true });
    tex->set_data(data, width * height * channels);
    stbi_image_free(data);
    return tex;
}
