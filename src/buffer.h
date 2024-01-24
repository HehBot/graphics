#ifndef BUFFER_H
#define BUFFER_H

#include <memory>
#include <string>
#include <vector>

enum class ShaderDataType {
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
};

static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    case ShaderDataType::Mat3:
        return 4 * 3 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4 * 4;
    case ShaderDataType::Int:
        return 4;
    case ShaderDataType::Int2:
        return 4 * 2;
    case ShaderDataType::Int3:
        return 4 * 3;
    case ShaderDataType::Int4:
        return 4 * 4;
    case ShaderDataType::Bool:
        return 1;
    }
    return 0;
}

struct BufferElement {
public:
    std::string name;
    ShaderDataType type;
    uint32_t size;
    bool normalised;
    size_t offset;

    BufferElement() = default;
    BufferElement(ShaderDataType type, std::string const& name, bool normalised = false)
        : name(name), type(type), size(ShaderDataTypeSize(type)), normalised(normalised), offset(0)
    {
    }

    uint32_t get_component_count() const
    {
        switch (type) {
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        case ShaderDataType::Mat3:
            return 3; // 3 x 3
        case ShaderDataType::Mat4:
            return 4; // 4 x 4
        case ShaderDataType::Int:
            return 1;
        case ShaderDataType::Int2:
            return 2;
        case ShaderDataType::Int3:
            return 3;
        case ShaderDataType::Int4:
            return 4;
        case ShaderDataType::Bool:
            return 1;
        }
        return 0;
    }
};

class BufferLayout {
public:
    BufferLayout() = default;
    BufferLayout(std::initializer_list<BufferElement> elements)
        : elements(elements)
    {
        calculate_offsets_and_strides();
    }

    uint32_t get_stride() const { return stride; }
    std::vector<BufferElement> const& get_elements() const { return elements; }

    std::vector<BufferElement>::iterator begin() { return elements.begin(); }
    std::vector<BufferElement>::iterator end() { return elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

private:
    void calculate_offsets_and_strides()
    {
        size_t offset = 0;
        for (auto& element : elements) {
            element.offset = offset;
            offset += element.size;
        }
        stride = offset;
    }
    std::vector<BufferElement> elements;
    uint32_t stride = 0;
};

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void set_data(void const* data, uint32_t size) = 0;

    virtual BufferLayout const& get_layout() const = 0;
    virtual void set_layout(BufferLayout const& layout) = 0;

    static std::shared_ptr<VertexBuffer> create(uint32_t size);
    static std::shared_ptr<VertexBuffer> create(float* vertices, uint32_t size);
};

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void bind() const = 0;

    virtual uint32_t get_count() const = 0;

    static std::shared_ptr<IndexBuffer> create(uint32_t* indices, uint32_t count);
};

#endif // BUFFER_H
