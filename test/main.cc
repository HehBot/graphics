#include <buffer.h>
#include <event.h>
#include <graphicscontext.h>
#include <iostream>
#include <memory>
#include <renderer.h>
#include <shader.h>
#include <vertexarray.h>
#include <window.h>

int main()
{
    std::shared_ptr<GraphicsContext> context = GraphicsContext::create();
    std::unique_ptr<Window> window = Window::create(context, Window::Prop { "graphics", 800, 600 });
    std::unique_ptr<Renderer> renderer = Renderer::create();
    std::shared_ptr<Shader> shader = Shader::create({ "test/vert.glsl", "test/frag.glsl" });

    bool window_should_close = false;

    EventCallbackFn callback = [&window_should_close](Event& event) {
        event.handled = true;
        switch (event.get_type()) {
        case EventType::WindowClose:
            window_should_close = true;
            break;
        case EventType::KeyPressed: {
            KeyPressedEvent& e = dynamic_cast<KeyPressedEvent&>(event);
            if (e.get_key() == Key::Escape)
                window_should_close = true;
            break;
        }
        default:
            event.handled = false;
        }
    };
    window->set_event_callback(callback);

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

    while (!window_should_close) {
        renderer->set_clear_color({ 0.2f, 0.3f, 0.3f, 1.0f });
        renderer->clear();

        // draw our first triangle
        shader->bind();
        renderer->draw_indexed(vao, index_count);

        window->on_update();
    }

    return 0;
}
