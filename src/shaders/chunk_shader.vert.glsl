#version 330 core

layout (location = 0) in vec3 a_pos;

uniform mat4 u_projection;
uniform mat4 u_view;

void main() {
  gl_Position = u_projection * u_view * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}
