#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <cstdint>
#include <glm/glm.hpp>
#include <renderer.h>

class OpenGLRenderer : public Renderer {
public:
    virtual void init() override;

    virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void set_clear_color(glm::vec4 const& color) override;
    virtual void clear() override;

    //         virtual void draw_indexed(std::shared_ptr<VertexArray> vertex_array, uint32_t indexCount) override;
    //         virtual void draw_lines(std::shared_ptr<VertexArray> vertex_array, uint32_t vertex_count) override;
    virtual void draw_indexed(int vertex_array, uint32_t indexCount) override;
    virtual void draw_lines(int vertex_array, uint32_t vertex_count) override;
};

#endif // OPENGLRENDERER_H
