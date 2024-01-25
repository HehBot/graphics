#include "glad/glad.h"
#include "vertexarray.h"

#include <cassert>
#include <memory>
#include <util/scopedbind.h>

using namespace graphics;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::Float:
        return GL_FLOAT;
    case ShaderDataType::Float2:
        return GL_FLOAT;
    case ShaderDataType::Float3:
        return GL_FLOAT;
    case ShaderDataType::Float4:
        return GL_FLOAT;
    case ShaderDataType::Mat3:
        return GL_FLOAT;
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
        return GL_INT;
    case ShaderDataType::Int2:
        return GL_INT;
    case ShaderDataType::Int3:
        return GL_INT;
    case ShaderDataType::Int4:
        return GL_INT;
    case ShaderDataType::Bool:
        return GL_BOOL;
    }

    assert(false && "Unknown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &id);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    if (current == this)
        current = nullptr;
    glDeleteVertexArrays(1, &id);
}

void OpenGLVertexArray::bind() const
{
    if (current != this) {
        current = this;
        glBindVertexArray(id);
    }
}

void OpenGLVertexArray::add_vertex_buffer(std::shared_ptr<VertexBuffer> const& vertex_buffer)
{
    auto const& layout = vertex_buffer->get_layout();
    assert(layout.get_elements().size() != 0 && "Vertex Buffer had no layout!");

    ScopedBind<VertexArray> scoped_bind(this);
    vertex_buffer->bind();

    for (auto const& element : layout) {
        switch (element.type) {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4: {
            glEnableVertexAttribArray(vertex_attr_index);
            glVertexAttribPointer(vertex_attr_index,
                                  element.get_component_count(),
                                  ShaderDataTypeToOpenGLBaseType(element.type),
                                  element.normalised ? GL_TRUE : GL_FALSE,
                                  layout.get_stride(),
                                  (void const*)element.offset);
            vertex_attr_index++;
            break;
        }
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4: {
            glEnableVertexAttribArray(vertex_attr_index);
            glVertexAttribIPointer(vertex_attr_index,
                                   element.get_component_count(),
                                   ShaderDataTypeToOpenGLBaseType(element.type),
                                   layout.get_stride(),
                                   (void const*)element.offset);
            vertex_attr_index++;
            break;
        }
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4: {
            uint8_t count = element.get_component_count();
            for (uint8_t i = 0; i < count; ++i) {
                glEnableVertexAttribArray(vertex_attr_index);
                glVertexAttribPointer(vertex_attr_index,
                                      count,
                                      ShaderDataTypeToOpenGLBaseType(element.type),
                                      element.normalised ? GL_TRUE : GL_FALSE,
                                      layout.get_stride(),
                                      (void const*)(element.offset + sizeof(float) * count * i));
                glVertexAttribDivisor(vertex_attr_index, 1);
                vertex_attr_index++;
            }
            break;
        }
        default:
            assert(false && "Unknown ShaderDataType");
        }
    }
    vertex_buffers.push_back(vertex_buffer);
}

void OpenGLVertexArray::set_index_buffer(std::shared_ptr<IndexBuffer> const& index_buffer)
{
    glBindVertexArray(id);
    index_buffer->bind();

    this->index_buffer = index_buffer;
}
