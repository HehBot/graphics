#include "glad/glad.h"
#include "renderer.h"

#include <initializer_list>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <util/scopedbind.h>
#include <vertexarray.h>

using namespace graphics;

OpenGLRenderer::OpenGLRenderer(Window const* window, std::initializer_list<Renderer::Option> opt)
    : window(window), mode(2)
{
    ScopedBind<Window> scoped_bind(window);
    static std::unordered_map<Renderer::Option, int> const convert = {
        { Option::CullFace, GL_CULL_FACE },
        { Option::DepthTest, GL_DEPTH_TEST },
    };
    for (auto const& o : opt) {
        GLenum g = 0;
        switch (o) {
        case Renderer::Option::CullFace:
            g = GL_CULL_FACE;
            break;
        case Renderer::Option::DepthTest:
            g = GL_DEPTH_TEST;
            break;
        }
        glEnable(g);
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGLRenderer::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    ScopedBind<Window> scoped_bind(window);
    glViewport(x, y, width, height);
}
void OpenGLRenderer::set_clear_color(glm::vec4 const& color)
{
    ScopedBind<Window> scoped_bind(window);
    glClearColor(color.r, color.g, color.b, color.a);
}
void OpenGLRenderer::clear()
{
    ScopedBind<Window> scoped_bind(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGLRenderer::enable_point_mode()
{
    if (mode != 0) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        mode = 0;
    }
}
void OpenGLRenderer::enable_line_mode()
{
    if (mode != 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        mode = 1;
    }
}
void OpenGLRenderer::enable_fill_mode()
{
    if (mode != 2) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        mode = 2;
    }
}

void OpenGLRenderer::draw_indexed(std::shared_ptr<VertexArray> vertex_array, uint32_t index_count)
{
    ScopedBind<VertexArray> scoped_bind(vertex_array.get());
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}
void OpenGLRenderer::draw_lines(std::shared_ptr<VertexArray> vertex_array, uint32_t vertex_count)
{
    ScopedBind<VertexArray> scoped_bind(vertex_array.get());
    glDrawArrays(GL_LINES, 0, vertex_count);
}
void OpenGLRenderer::draw_triangles(std::shared_ptr<VertexArray> vertex_array, uint32_t vertex_count)
{
    ScopedBind<VertexArray> scoped_bind(vertex_array.get());
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}
