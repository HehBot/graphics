#include "shader.h"
#include "glad/glad.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

static GLenum shader_type_from_string(std::string const& type_str)
{
    if (type_str == "vertex")
        return GL_VERTEX_SHADER;
    else if (type_str == "fragment")
        return GL_FRAGMENT_SHADER;
    assert(false && "Unknown shader type");
}

static std::string read_file(std::string path, GLenum& type)
{
    std::ifstream f(path);

    std::string type_decl;
    std::getline(f, type_decl);

    std::string type_tag = "#type ";
    if (type_decl.substr(0, type_tag.length()) != type_tag)
        assert(false && "Syntax error");

    std::string type_str = type_decl.substr(type_tag.length(), type_decl.length() - 1);

    type = shader_type_from_string(type_str);

    std::stringstream buf;
    buf << f.rdbuf();

    assert(buf.str().length() != 0 && "Shader empty");

    return buf.str();
}

OpenGLShader::OpenGLShader(std::initializer_list<std::string> shaderpaths)
{
    std::vector<uint32_t> shader_ids;
    for (auto const& path : shaderpaths) {
        GLenum type;
        std::string source = read_file(path, type);

        uint32_t shader_id = glCreateShader(type);

        char const* w = source.c_str();
        glShaderSource(shader_id, 1, &w, nullptr);
        glCompileShader(shader_id);

        // check for shader compile errors
        int success;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader_id, 512, nullptr, infoLog);
            std::cerr << path << "ERROR::SHADER::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
            assert(false);
        }

        shader_ids.push_back(shader_id);
    }

    id = glCreateProgram();
    for (auto shader_id : shader_ids)
        glAttachShader(id, shader_id);
    glLinkProgram(id);

    // check for linking errors
    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::LINKING_FAILED\n"
                  << infoLog << std::endl;
        assert(false);
    }

    for (auto shader_id : shader_ids) {
        glDetachShader(id, shader_id);
        glDeleteShader(shader_id);
    }

    load_uniform_locs();
}
void OpenGLShader::load_uniform_locs()
{
    int count, bufSize;

    glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufSize);
    GLchar* name = new GLchar[bufSize];

    glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);
    for (int i = 0; i < count; i++) {
        glGetActiveUniform(id, i, bufSize, nullptr, nullptr, nullptr, name);
        uint32_t uniformLoc = glGetUniformLocation(id, name);
        uniforms.insert({ std::string(name), uniformLoc });
    }

    delete[] name;
}

OpenGLShader::~OpenGLShader()
{
    if (current == this)
        current = nullptr;
    glDeleteProgram(id);
}

void OpenGLShader::bind() const
{
    if (current != this) {
        current = this;
        glUseProgram(id);
    }
}

void OpenGLShader::set_int(std::string const& name, int value)
{
    ScopedBind<Shader> scoped_bind(this);
    glUniform1i(uniform_loc(name), value);
}
void OpenGLShader::set_int_array(std::string const& name, int* values, uint32_t count)
{
    ScopedBind<Shader> scoped_bind(this);
    glUniform1iv(uniform_loc(name), count, values);
}
void OpenGLShader::set_float(std::string const& name, float value)
{
    ScopedBind<Shader> scoped_bind(this);
    glUniform1f(uniform_loc(name), value);
}
void OpenGLShader::set_float2(std::string const& name, glm::vec2 const& value)
{
    ScopedBind<Shader> scoped_bind(this);
    glUniform2f(uniform_loc(name), value.x, value.y);
}
void OpenGLShader::set_float3(std::string const& name, glm::vec3 const& value)
{
    ScopedBind<Shader> scoped_bind(this);
    glUniform3f(uniform_loc(name), value.x, value.y, value.z);
}
void OpenGLShader::set_float4(std::string const& name, glm::vec4 const& value)
{
    ScopedBind<Shader> scoped_bind(this);
    glUniform4f(uniform_loc(name), value.x, value.y, value.z, value.w);
}
void OpenGLShader::set_mat4(std::string const& name, glm::mat4 const& mat)
{
    ScopedBind<Shader> scoped_bind(this);
    glUniformMatrix4fv(uniform_loc(name), 1, GL_FALSE, glm::value_ptr(mat));
}

uint32_t OpenGLShader::uniform_loc(std::string const& name) const
{
    auto search = uniforms.find(name);
    if (search == uniforms.end()) {
        std::cerr << "Uniform " << name << " not found\n";
        assert(false);
    }
    return search->second;
}
