#version 330 core

out vec4 FRAGCOLOR;

in vec3 TEXCOORD;

uniform samplerCube SKYBOX;

void main() {
  FRAGCOLOR = texture(SKYBOX, TEXCOORD);
}
