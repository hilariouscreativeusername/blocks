#version 330 core

layout (location = 0) out vec4 o_colour;

in vec3 v_tex;
in float v_light;

uniform sampler2DArray u_texture;

void main() {
  o_colour = texture(u_texture, v_tex);
  if (o_colour.a < 0.5) {
    discard;
  }
  o_colour.xyz *= v_light;
}
