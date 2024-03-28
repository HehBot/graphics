#include <buffer.h>
#include <context.h>
#include <event.h>
#include <ft2build.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>
#include <renderer.h>
#include <shader.h>
#include <texture.h>
#include <vertexarray.h>
#include <window.h>
#include FT_FREETYPE_H

using namespace graphics;

std::shared_ptr<Texture> ft_load_glyph(char const* path, char x, glm::ivec2& size, glm::ivec2& bearing)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return nullptr;
    }
    FT_Face face;
    if (FT_New_Face(ft, path, 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return nullptr;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, x, FT_LOAD_RENDER)) {
        std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
        return nullptr;
    }

    size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
    bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
    std::shared_ptr<Texture> tex = Texture2D::create({ (uint32_t)size.x, (uint32_t)size.y, ImageFormat::R8, true });
    tex->set_data(face->glyph->bitmap.buffer, size.x * size.y * 1);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return tex;
}

int main()
{
    std::shared_ptr<Context> context = Context::create();

    std::unique_ptr<Window> window = Window::create(context, Window::Prop { "graphics", 1000, 1000 });
    window->bind();

    std::unique_ptr<Renderer> renderer = Renderer::create(window.get(), { Renderer::Option::DepthTest, Renderer::Option::CullFace });

    bool window_should_close = false;
    std::function<void(Event&)> callback = [&window_should_close, &renderer](Event& event) {
        event.handled = true;
        switch (event.get_type()) {
        case EventType::WindowClose:
            window_should_close = true;
            break;
        case EventType::KeyPressed: {
            KeyPressedEvent& e = dynamic_cast<KeyPressedEvent&>(event);
            if (e.get_key() == Key::ESCAPE)
                window_should_close = true;
            break;
        }
        case EventType::WindowResize: {
            WindowResizeEvent& e = dynamic_cast<WindowResizeEvent&>(event);
            renderer->set_viewport(0, 0, e.get_width(), e.get_height());
            break;
        }
        default:
            event.handled = false;
        }
    };
    window->set_event_callback(callback);

    std::shared_ptr<Shader> shader = Shader::create({ "shaders/vert.glsl", "shaders/frag.glsl" });
    shader->bind();

    shader->set_int("text", 0);
    glm::ivec2 size, bearing;
    std::shared_ptr<Texture> tex = ft_load_glyph("arial.ttf", 'a', size, bearing);
    tex->bind_to_slot(0);

    glm::vec3 text_color(0.5f, 0.8f, 0.2f);
    float x = 25.0f, y = 25.0f, scale = 1.0f;

    float xpos = x + bearing.x * scale, ypos = y - (size.y - bearing.y) * scale;
    float w = size.x * scale, h = size.y * scale;

    float vertices[6][4] = {
        { xpos, ypos, 0.0f, 1.0f },
        { xpos, ypos + h, 0.0f, 0.0f },
        { xpos + w, ypos, 1.0f, 1.0f },
        { xpos + w, ypos + h, 1.0f, 0.0f }
    };
    uint32_t indices[6] = {
        1, 0, 2,
        1, 2, 3
    };
    uint32_t index_count = sizeof(indices) / sizeof(indices[0]);

    std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create(&vertices[0][0], sizeof(vertices));
    vbo->set_layout({ { ShaderDataType::Float2, "a_pos" }, { ShaderDataType::Float2, "a_tex_coord" } });
    std::shared_ptr<IndexBuffer> ibo = IndexBuffer::create(indices, index_count);

    std::shared_ptr<VertexArray> vao = VertexArray::create();
    vao->bind();

    vao->add_vertex_buffer(vbo);
    vao->set_index_buffer(ibo);

    glm::mat4 projection = glm::ortho(0.0f, (float)window->width, 0.0f, (float)window->height);
    shader->set_mat4("projection", projection);
    shader->set_float3("text_color", text_color);

    renderer->set_clear_color({ 0.2f, 0.3f, 0.3f, 1.0f });

    while (!window_should_close) {
        renderer->clear();
        renderer->draw_indexed(vao, index_count);
        window->on_update();
    }

    return 0;
}
