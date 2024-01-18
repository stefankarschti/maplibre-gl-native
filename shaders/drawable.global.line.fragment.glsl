#ifdef GL_ES
precision highp float;
#endif

uniform vec4 u_color;
void main() {
    fragColor = u_color;
}
