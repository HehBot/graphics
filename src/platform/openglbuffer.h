#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include <buffer.h>

class OpenGLVertexBuffer : public VertexBuffer {
public:
    OpenGLVertexBuffer(uint32_t size);
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void set_data(void const* data, uint32_t size) override;

    virtual BufferLayout const& get_layout() const override { return layout; }
    virtual void set_layout(BufferLayout const& layout) override { this->layout = layout; }

private:
    uint32_t id;
    BufferLayout layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual uint32_t get_count() const override { return count; }

private:
    uint32_t id;
    uint32_t count;
};

#endif // OPENGLBUFFER_H
