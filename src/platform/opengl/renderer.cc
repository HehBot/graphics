#include "renderer.h"
#include "glad/glad.h"

#include <iostream>
#include <memory>
#include <util/scopedbind.h>
#include <vertexarray.h>

OpenGLRenderer::OpenGLRenderer(Window const* window)
    : window(window)
{
    ScopedBind<Window> scoped_bind(window);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    glClear(GL_COLOR_BUFFER_BIT);
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
