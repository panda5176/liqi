#version 330 core
layout (location = 0) in vec3 APOS;
layout (location = 1) in vec3 ANORMAL;
layout (location = 2) in vec2 ATEXCOORD;

out vec3 FRAGPOS;
out vec3 NORMAL;
out vec2 TEXCOORD;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

void main() {
  gl_Position = PROJECTION * VIEW * MODEL * vec4(APOS, 1.0);
  FRAGPOS = vec3(MODEL * vec4(APOS, 1.0)); // Fragment position at world space
  NORMAL = mat3(transpose(inverse(MODEL))) * ANORMAL; // Normal is non-uniform
  TEXCOORD = ATEXCOORD;
}
