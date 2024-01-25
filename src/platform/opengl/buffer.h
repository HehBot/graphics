#ifndef PLATFORM_OPENGL_BUFFER_H
#define PLATFORM_OPENGL_BUFFER_H

#include <buffer.h>

class OpenGLVertexBuffer : public graphics::VertexBuffer {
public:
    OpenGLVertexBuffer(uint32_t size);
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void bind() const override;
    virtual void set_data(void const* data, uint32_t size) override;

    virtual graphics::BufferLayout const& get_layout() const override { return layout; }
    virtual void set_layout(graphics::BufferLayout const& layout) override { this->layout = layout; }

private:
    uint32_t id;
    graphics::BufferLayout layout;
};

class OpenGLIndexBuffer : public graphics::IndexBuffer {
public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    virtual void bind() const override;

    virtual uint32_t get_count() const override { return count; }

private:
    uint32_t id;
    uint32_t count;
};

#endif // PLATFORM_OPENGL_BUFFER_H
