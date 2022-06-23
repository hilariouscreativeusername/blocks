#version 330 core

layout (location = 0) out vec4 o_colour;

in vec2 v_tex;

void main() {
  o_colour = vec4(v_tex, 0, 1);
}
