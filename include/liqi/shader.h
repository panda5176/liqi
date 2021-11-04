#ifndef LIQI_SHADER_H_
#define LIQI_SHADER_H_

#ifndef LIQI_LIBRARY_H_
#define LIQI_LIBRARY_H_

// glad
#include <glad/glad.h>

// glfw
#define GLFW_INCLUDE_NONE  // Prevents collision between glad and glfw
#include <GLFW/glfw3.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// stb
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

// assimp
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>

// standard
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#endif  // LIQI_LIBRARY_H_

namespace liqi {
class Shader {
 public:
  void Use() { glUseProgram(program_); }

  void Build(const char* vertex_shader_file_path,
             const char* fragment_shader_file_path) {
    // Read, compile, link shader program
    // Load vertex shader
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    std::string shader_source = ReadSource_(vertex_shader_file_path, "VERTEX");
    const char* vertex_shader_source = shader_source.c_str();
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    CheckCompilation_(vertex_shader, "VERTEX");

    // Load fragment shader
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    shader_source = ReadSource_(fragment_shader_file_path, "FRAGMENT");
    const char* fragment_shader_source = shader_source.c_str();
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    CheckCompilation_(fragment_shader, "FRAGMENT");

    // Link shaders within shader program
    program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader);
    glAttachShader(program_, fragment_shader);
    glLinkProgram(program_);
    CheckLinkage_(program_);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
  }

  void SetUniformInt_(const std::string& uniform_name, const int value) {
    // Set 1st dimension int uniform to program
    glUniform1i(glGetUniformLocation(program_, uniform_name.c_str()), value);
  }

  void SetUniformFloat_(const std::string& uniform_name, const float value) {
    // Set 1st dimension float uniform to program
    glUniform1f(glGetUniformLocation(program_, uniform_name.c_str()), value);
  }

  void SetUniformVec3_(const std::string& uniform_name, const glm::vec3 value) {
    // Set 3rd dimension float vec3 uniform to program
    glUniform3fv(glGetUniformLocation(program_, uniform_name.c_str()), 1,
                 glm::value_ptr(value));
  }

  void SetUniformMat4_(const std::string& uniform_name, const glm::mat4 value) {
    // Set 4th dimension float mat4 uniform to program
    glUniformMatrix4fv(glGetUniformLocation(program_, uniform_name.c_str()), 1,
                       GL_FALSE, glm::value_ptr(value));
  }

  void SetTransform(const glm::mat4 view_transform,
                    const glm::mat4 proj_transform,
                    const glm::mat4 model_transform) {
    SetUniformMat4_("VIEW", view_transform);
    SetUniformMat4_("PROJECTION", proj_transform);
    SetUniformMat4_("MODEL", model_transform);
  }

  void SetTransform(const glm::mat4 view_transform,
                    const glm::mat4 proj_transform) {
    SetUniformMat4_("VIEW", view_transform);
    SetUniformMat4_("PROJECTION", proj_transform);
  }

  void SetModel(const glm::mat4 model_transform) {
    SetUniformMat4_("MODEL", model_transform);
  }

  void SetMaterial(const int diffuse, const int specular,
                   const float shininess) {
    SetUniformInt_("MATERIAL.diffuse", diffuse);
    SetUniformInt_("MATERIAL.specular", specular);
    SetUniformFloat_("MATERIAL.shininess", shininess);
  }

  void SetAttnConst(const float constant, const float linear,
                    const float quadratic) {
    SetUniformFloat_("ATTNCONST.constant", constant);
    SetUniformFloat_("ATTNCONST.linear", linear);
    SetUniformFloat_("ATTNCONST.quadratic", quadratic);
  }

  void SetDirLight(const glm::vec3 direction, const glm::vec3 ambient,
                   const glm::vec3 diffuse, const glm::vec3 specular) {
    SetUniformVec3_("DIRLIGHT.direction", direction);
    SetUniformVec3_("DIRLIGHT.ambient", ambient);
    SetUniformVec3_("DIRLIGHT.diffuse", diffuse);
    SetUniformVec3_("DIRLIGHT.specular", specular);
  }

  void SetPointLight(const glm::vec3 position, const glm::vec3 ambient,
                     const glm::vec3 diffuse, const glm::vec3 specular,
                     const unsigned int idx) {
    std::string prefix = "POINTLIGHTS[" + std::to_string(idx);
    const char* position_uniform = (prefix + "].position").c_str();
    const char* ambient_uniform = (prefix + "].ambient").c_str();
    const char* diffuse_uniform = (prefix + "].diffuse").c_str();
    const char* specular_uniform = (prefix + "].specular").c_str();
    SetUniformVec3_(position_uniform, position);
    SetUniformVec3_(ambient_uniform, ambient);
    SetUniformVec3_(diffuse_uniform, diffuse);
    SetUniformVec3_(specular_uniform, specular);
  }

  void SetSpotLight(const glm::vec3 position, const glm::vec3 direction,
                    const glm::vec3 ambient, const glm::vec3 diffuse,
                    const glm::vec3 specular, const float cos_phi,
                    const float cos_gamma) {
    SetUniformVec3_("SPOTLIGHT.position", position);
    SetUniformVec3_("SPOTLIGHT.direction", direction);
    SetUniformVec3_("SPOTLIGHT.ambient", ambient);
    SetUniformVec3_("SPOTLIGHT.diffuse", diffuse);
    SetUniformVec3_("SPOTLIGHT.specular", specular);
    SetUniformFloat_("SPOTLIGHT.flashCosPhi", cos_phi);
    SetUniformFloat_("SPOTLIGHT.flashCosGamma", cos_gamma);
  }

  void SetCamPos(const glm::vec3 cam_pos) {
    SetUniformVec3_("CAMPOS", cam_pos);
  }

  void SetShininess(const float shininess) {
    SetUniformFloat_("SHININESS", shininess);
  }

 private:
  unsigned int program_;

  std::string ReadSource_(const char* file_path,
                          const std::string shader_name) {
    // Read GLSL shader source file
    std::string line, shader_source = "";
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) {
      std::cout << "ERROR::SHADER::" << shader_name
                << "::FILE_OPEN_FAILED::" << file_path << std::endl;
      throw 1;
    }
    while (std::getline(file_stream, line)) {
      shader_source += line + "\n";
    }
    file_stream.close();
    return shader_source;
  }

  bool CheckCompilation_(const unsigned int shader,
                         const std::string shader_name) {
    // Check if shader compilation succeeded
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::" << shader_name
                << "::COMPILATION_FAILED::" << infoLog << std::endl;
      throw 2;
    }
    return true;
  }

  bool CheckLinkage_(const unsigned int program) {
    // Check if shader program link succeeded
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(program, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED::" << infoLog
                << std::endl;
      throw 3;
    }
    return true;
  }
};
}  // namespace liqi

#endif  // LIQI_SHADER_H_
