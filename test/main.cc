#include "stb_image/stb_image.h"

#include <buffer.h>
#include <event.h>
#include <graphicscontext.h>
#include <iostream>
#include <memory>
#include <renderer.h>
#include <shader.h>
#include <texture.h>
#include <vertexarray.h>
#include <window.h>

std::shared_ptr<Texture> stbi_load_texture(char const* path)
{
    static bool inited = false;
    if (!inited)
        stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);
    std::shared_ptr<Texture> tex = Texture2D::create({ (uint32_t)width, (uint32_t)height, (channels == 4 ? ImageFormat::RGBA8 : ImageFormat::RGB8), true });
    tex->set_data(data, width * height * channels);
    stbi_image_free(data);
    return tex;
}

int main()
{
    std::shared_ptr<GraphicsContext> context = GraphicsContext::create();
    std::unique_ptr<Window> window = Window::create(context, Window::Prop { "graphics", 1000, 1000 });
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
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.9f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
    };
    uint32_t indices[] = {
        0, 1, 3, // first Triangle
        1, 2, 3 // second Triangle
    };
    uint32_t index_count = sizeof(indices) / sizeof(indices[0]);

    std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create(vertices, sizeof(vertices));
    vbo->set_layout({ { ShaderDataType::Float3, "aPos" }, { ShaderDataType::Float3, "aColor" }, { ShaderDataType::Float2, "aTexCoord" } });
    std::shared_ptr<IndexBuffer> ibo = IndexBuffer::create(indices, index_count);
    std::shared_ptr<VertexArray> vao = VertexArray::create();

    vao->add_vertex_buffer(vbo);
    vao->set_index_buffer(ibo);

    std::shared_ptr<Texture> tex1 = stbi_load_texture("test/awesomeface.png");
    std::shared_ptr<Texture> tex2 = stbi_load_texture("test/wall.jpg");

    shader->bind();
    shader->set_int("texture1", 0);
    tex1->bind(0);
    shader->set_int("texture2", 1);
    tex2->bind(1);

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
