#version 330 core

layout (location = 0) out vec4 o_colour;

in vec2 v_tex;

uniform sampler2D u_texture;

void main() {
  o_colour = texture(u_texture, v_tex);
}
