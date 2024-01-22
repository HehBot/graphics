#include "opengltexture.h"

#include <cassert>
#include <glad/glad.h>

static GLenum image_format_to_gl_internal_format(ImageFormat format)
{
    switch (format) {
    case ImageFormat::RGB8:
        return GL_RGB8;
    case ImageFormat::RGBA8:
        return GL_RGBA8;
    default:
        assert(false);
    }
}

static GLenum image_format_to_gl_data_format(ImageFormat format)
{
    switch (format) {
    case ImageFormat::RGB8:
        return GL_RGB;
    case ImageFormat::RGBA8:
        return GL_RGBA;
    default:
        assert(false);
    }
}

OpenGLTexture2D::OpenGLTexture2D(Texture::Spec const& spec)
    : width(spec.width), height(spec.height), interal_format(image_format_to_gl_internal_format(spec.format)), data_format(image_format_to_gl_data_format(spec.format))
{
    glCreateTextures(GL_TEXTURE_2D, 1, &id);
    glTextureStorage2D(id, 1, interal_format, width, height);

    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (spec.gen_mips)
        glGenerateMipmap(GL_TEXTURE_2D);
}
OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &id);
}

void OpenGLTexture2D::set_data(void* data, uint32_t size)
{
    uint32_t bpp = (data_format == GL_RGBA ? 4 : 3);
    assert(size == width * height * bpp && "Data must be entire texture!");
    glTextureSubImage2D(id, 0, 0, 0, width, height, data_format, GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}
