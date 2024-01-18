// Generated code, do not modify this file!
#pragma once
#include <mbgl/shaders/shader_source.hpp>

namespace mbgl {
namespace shaders {

template <>
struct ShaderSource<BuiltIn::GlobalLineShader, gfx::Backend::Type::OpenGL> {
    static constexpr const char* name = "GlobalLineShader";
    static constexpr const char* vertex = R"(#ifdef GL_ES
precision highp float;
#endif

layout (location = 0) in vec2 a_pos;
uniform mat4 u_matrix;
void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
}
)";
    static constexpr const char* fragment = R"(#ifdef GL_ES
precision highp float;
#endif

uniform vec4 u_color;
void main() {
    fragColor = u_color;
}
)";
};

} // namespace shaders
} // namespace mbgl
