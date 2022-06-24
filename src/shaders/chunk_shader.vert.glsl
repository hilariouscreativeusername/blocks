#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_tex;
layout (location = 2) in float a_light;

out vec3 v_tex;
out float v_light;

uniform mat4 u_projection;
uniform mat4 u_view;

void main() {
  v_tex = a_tex;
  v_light = a_light;

  gl_Position = u_projection * u_view * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}
