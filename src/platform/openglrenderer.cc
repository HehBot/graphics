#include "openglrenderer.h"

#include <glad/glad.h>
#include <iostream>
#include <memory>
#include <vertexarray.h>

void OpenGLRenderer::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}
void OpenGLRenderer::set_clear_color(glm::vec4 const& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}
void OpenGLRenderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::draw_indexed(std::shared_ptr<VertexArray> vertex_array, uint32_t index_count)
{
    vertex_array->bind();
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}
void OpenGLRenderer::draw_lines(std::shared_ptr<VertexArray> vertex_array, uint32_t vertex_count)
{
    vertex_array->bind();
    glDrawArrays(GL_LINES, 0, vertex_count);
}
