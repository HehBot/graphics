#ifndef PLATFORM_OPENGL_VERTEXARRAY_H
#define PLATFORM_OPENGL_VERTEXARRAY_H

#include <memory>
#include <vector>
#include <vertexarray.h>

class OpenGLVertexArray : public graphics::VertexArray {
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void bind() const override;

    virtual void add_vertex_buffer(std::shared_ptr<graphics::VertexBuffer> const& vertex_buffer) override;
    virtual void set_index_buffer(std::shared_ptr<graphics::IndexBuffer> const& index_buffer) override;

    virtual std::vector<std::shared_ptr<graphics::VertexBuffer>> const& get_vertex_buffers() const override { return vertex_buffers; }
    virtual std::shared_ptr<graphics::IndexBuffer> const& get_index_buffer() const override { return index_buffer; }

private:
    uint32_t id;
    uint32_t vertex_attr_index = 0;
    std::vector<std::shared_ptr<graphics::VertexBuffer>> vertex_buffers;
    std::shared_ptr<graphics::IndexBuffer> index_buffer;
};

#endif // PLATFORM_OPENGL_VERTEXARRAY_H
