#version 330 core
layout (location = 0) in vec3 APOS;

out vec3 TEXCOORD;

uniform mat4 VIEW;
uniform mat4 PROJECTION;

void main() {
  gl_Position = (PROJECTION * VIEW * vec4(APOS, 1.0)).xyww; // z to 1.0
  TEXCOORD = APOS;
}
