#include <GLFW/glfw3.h>
#include <buffer.h>
#include <graphicscontext.h>
#include <iostream>
#include <memory>
#include <renderer.h>
#include <shader.h>
#include <vertexarray.h>
#include <window.h>

void framebuffer_size_callback(GLFWwindow* _w, int width, int height);
void processInput(GLFWwindow* _w);

unsigned int const SCR_WIDTH = 800, SCR_HEIGHT = 600;

int main()
{
    std::shared_ptr<GraphicsContext> context = GraphicsContext::create();
    std::unique_ptr<Window> window = Window::create(context, Window::Prop { "graphics", SCR_WIDTH, SCR_HEIGHT });

    GLFWwindow* _w = (GLFWwindow*)window->get_native_handle();
    //     glfwSetFramebufferSizeCallback(_w, framebuffer_size_callback);

    std::unique_ptr<Renderer> renderer = Renderer::create();
    std::shared_ptr<Shader> shader = Shader::create({ "test/vert.glsl", "test/frag.glsl" });

    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };
    uint32_t indices[] = {
        0, 1, 3, // first Triangle
        1, 2, 3 // second Triangle
    };
    uint32_t index_count = sizeof(indices) / sizeof(indices[0]);

    std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create(vertices, sizeof(vertices));
    vbo->set_layout({ { ShaderDataType::Float3, "aPos" } });
    std::shared_ptr<IndexBuffer> ibo = IndexBuffer::create(indices, index_count);
    std::shared_ptr<VertexArray> vao = VertexArray::create();

    vao->add_vertex_buffer(vbo);
    vao->set_index_buffer(ibo);

    //     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(_w)) {
        processInput(_w);

        renderer->set_clear_color({ 0.2f, 0.3f, 0.3f, 1.0f });
        renderer->clear();

        // draw our first triangle
        shader->bind();
        renderer->draw_indexed(vao, index_count);

        window->swap_buffers();
        glfwPollEvents();
    }

    return 0;
}

void processInput(GLFWwindow* _w)
{
    if (glfwGetKey(_w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_w, true);
}

// void framebuffer_size_callback(GLFWwindow* _w, int width, int height)
// {
//     // make sure the viewport matches the new _w dimensions; note that width and
//     // height will be significantly larger than specified on retina displays.
//     glViewport(0, 0, width, height);
// }
