#ifndef PLATFORM_OPENGL_SHADER_H
#define PLATFORM_OPENGL_SHADER_H

#include <glm/glm.hpp>
#include <shader.h>
#include <unordered_map>

class OpenGLShader : public Shader {
public:
    OpenGLShader(std::initializer_list<std::string> shaderpaths);
    virtual ~OpenGLShader();

    virtual void bind() const override;

    virtual void set_int(std::string const& name, int value) override;
    virtual void set_int_array(std::string const& name, int* values, uint32_t count) override;

    virtual void set_float(std::string const& name, float value) override;
    virtual void set_float2(std::string const& name, glm::vec2 const& value) override;
    virtual void set_float3(std::string const& name, glm::vec3 const& value) override;
    virtual void set_float4(std::string const& name, glm::vec4 const& value) override;
    virtual void set_mat4(std::string const& name, glm::mat4 const& value) override;

private:
    void load_uniform_locs();
    uint32_t uniform_loc(std::string const& name) const;

private:
    uint32_t id;
    std::unordered_map<std::string, uint32_t> uniforms;
};

#endif // PLATFORM_OPENGL_SHADER_H
