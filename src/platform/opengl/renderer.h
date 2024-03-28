#ifndef PLATFORM_OPENGL_RENDERER_H
#define PLATFORM_OPENGL_RENDERER_H

#include <cstdint>
#include <glm/glm.hpp>
#include <renderer.h>
#include <window.h>

class OpenGLRenderer : public graphics::Renderer {
public:
    OpenGLRenderer(graphics::Window const* window, std::initializer_list<graphics::Renderer::Option> opt);
    virtual ~OpenGLRenderer() = default;
    virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void set_clear_color(glm::vec4 const& color) override;
    virtual void clear() override;

    virtual void draw_indexed(std::shared_ptr<graphics::VertexArray> vertex_array, uint32_t indexCount) override;
    virtual void draw_lines(std::shared_ptr<graphics::VertexArray> vertex_array, uint32_t vertex_count) override;
    virtual void draw_triangles(std::shared_ptr<graphics::VertexArray> vertex_array, uint32_t vertex_count) override;

private:
    graphics::Window const* window;
};

#endif // PLATFORM_OPENGL_RENDERER_H
