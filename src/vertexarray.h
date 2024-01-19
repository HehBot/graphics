#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <buffer.h>
#include <memory>

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void add_vertex_buffer(std::shared_ptr<VertexBuffer> const& vertex_buffer) = 0;
    virtual void set_index_buffer(std::shared_ptr<IndexBuffer> const& index_buffer) = 0;

    virtual std::vector<std::shared_ptr<VertexBuffer>> const& get_vertex_buffers() const = 0;
    virtual std::shared_ptr<IndexBuffer> const& get_index_buffer() const = 0;

    static std::shared_ptr<VertexArray> create();
};

#endif // VERTEXARRAY_H
