// Generated code, do not modify this file!
#pragma once
#include <mbgl/shaders/shader_source.hpp>

namespace mbgl {
namespace shaders {

template <>
struct ShaderSource<BuiltIn::CustomSymbolIconShader, gfx::Backend::Type::OpenGL> {
    static constexpr const char* name = "CustomSymbolIconShader";
    static constexpr const char* vertex = R"(layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec2 a_tex;

layout (std140) uniform SymbolDrawableUBO {
    highp mat4 u_matrix;
};

out vec2 v_tex;

void main() {
    v_tex = a_tex;
    gl_Position = u_matrix * vec4(a_pos, 0.0, 1.0);
}
)";
    static constexpr const char* fragment = R"(uniform sampler2D u_texture;

in vec2 v_tex;

void main() {
    fragColor = texture(u_texture, v_tex);
}
)";
};

} // namespace shaders
} // namespace mbgl