#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include <memory>

class Renderer {
public:
    enum class API {
        None = 0,
        OpenGL = 1
    };
    virtual ~Renderer() = default;

    virtual void init() = 0;

    virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void set_clear_color(glm::vec4 const& color) = 0;
    virtual void clear() = 0;

    //         virtual void draw_indexed(std::shared_ptr<VertexArray> vertex_array, uint32_t indexCount) = 0;
    //         virtual void draw_lines(std::shared_ptr<VertexArray> vertex_array, uint32_t vertex_count) = 0;
    virtual void draw_indexed(int vertex_array, uint32_t indexCount) = 0;
    virtual void draw_lines(int vertex_array, uint32_t vertex_count) = 0;

    static API get_api() { return api; }
    static std::unique_ptr<Renderer> create();

private:
    static API api;
};

#endif // RENDERER_H
