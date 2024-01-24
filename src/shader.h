#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <util/scopedbind.h>

class Shader {
public:
    virtual ~Shader() = default;

    virtual void bind() const = 0;

    virtual void set_int(std::string const& name, int value) = 0;
    virtual void set_int_array(std::string const& name, int* values, uint32_t count) = 0;

    virtual void set_float(std::string const& name, float value) = 0;
    virtual void set_float2(std::string const& name, glm::vec2 const& value) = 0;
    virtual void set_float3(std::string const& name, glm::vec3 const& value) = 0;
    virtual void set_float4(std::string const& name, glm::vec4 const& value) = 0;
    virtual void set_mat4(std::string const& name, glm::mat4 const& value) = 0;

    static std::shared_ptr<Shader> create(std::initializer_list<std::string> shaderpaths);

protected:
    static Shader const* current;
    friend class ScopedBind<Shader>;
};

#endif // SHADER_H
