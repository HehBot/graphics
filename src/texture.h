#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <string>

namespace graphics {
enum class ImageFormat {
    R8,
    RGB8,
    RGBA8,
    RGBA32F
};

class Texture {
public:
    struct Spec {
        uint32_t width = 1, height = 1;
        ImageFormat format = ImageFormat::RGBA8;
        bool gen_mips = true;
    };

    virtual ~Texture() = default;

    virtual uint32_t get_width() const = 0;
    virtual uint32_t get_height() const = 0;

    virtual void set_data(void* data, uint32_t size) = 0;
    virtual void bind_to_slot(uint32_t slot) const = 0;
};

class Texture2D : public Texture {
public:
    static std::shared_ptr<Texture2D> create(Texture::Spec const& spec);
};
}

#endif // TEXTURE_H
