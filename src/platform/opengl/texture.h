#ifndef PLATFORM_OPENGL_TEXTURE_H
#define PLATFORM_OPENGL_TEXTURE_H

#include "glad/glad.h"

#include <texture.h>

class OpenGLTexture2D : public Texture2D {
public:
    OpenGLTexture2D(Texture::Spec const& spec);
    virtual ~OpenGLTexture2D();

    virtual uint32_t get_width() const override { return width; }
    virtual uint32_t get_height() const override { return height; }

    virtual void set_data(void* data, uint32_t size);
    virtual void bind_to_slot(uint32_t slot) const override;

private:
    uint32_t id;

    std::string path;
    uint32_t width, height;
    GLenum interal_format, data_format;
};

#endif // PLATFORM_OPENGL_TEXTURE_H
