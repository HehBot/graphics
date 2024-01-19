#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include <memory>
#include <vector>
#include <vertexarray.h>

class OpenGLVertexArray : public VertexArray {
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void add_vertex_buffer(std::shared_ptr<VertexBuffer> const& vertex_buffer) override;
    virtual void set_index_buffer(std::shared_ptr<IndexBuffer> const& index_buffer) override;

    virtual std::vector<std::shared_ptr<VertexBuffer>> const& get_vertex_buffers() const override { return vertex_buffers; }
    virtual std::shared_ptr<IndexBuffer> const& get_index_buffer() const override { return index_buffer; }

private:
    uint32_t id;
    uint32_t vertex_attr_index = 0;
    std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers;
    std::shared_ptr<IndexBuffer> index_buffer;
};

#endif // OPENGLVERTEXARRAY_H
