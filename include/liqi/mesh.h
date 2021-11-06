#ifndef LIQI_MESH_H_
#define LIQI_MESH_H_

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

// imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// standard
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#endif  // LIQI_LIBRARY_H_

// liqi
#include <liqi/shader.h>

namespace liqi {
struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex_coords;
};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;
};

void BuildVertices(unsigned int* vao_ptr, unsigned int* vbo_ptr,
                   const float vertices[], const unsigned int vertices_size) {
  // Generate vertex array / vertex array buffer / element array buffer object
  glGenVertexArrays(1, vao_ptr);
  glGenBuffers(1, vbo_ptr);

  // Bind vertex to array objects
  glBindVertexArray(*vao_ptr);
  glBindBuffer(GL_ARRAY_BUFFER, *vao_ptr);
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

  // Set pointer to array objects
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void*)(6 * sizeof(float)));

  // Free memory
  glBindVertexArray(0);
}

int SetTexture(unsigned int* texture_ptr, const char* texture_file_path,
               const unsigned int texture_format) {
  // Set texture from read image data
  glGenTextures(1, texture_ptr);
  // glActiveTexture(GL_TEXTURE0);  // Maybe default depends on graphic driver
  glBindTexture(GL_TEXTURE_2D, *texture_ptr);

  // Texture wrapping and filtering options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Load texture image
  int width, height, nr_channels;  // The number of RGB channels
  unsigned char* data =
      stbi_load(texture_file_path, &width, &height, &nr_channels, 0);

  // Generate texture and mipmap
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, texture_format, width, height, 0,
                 texture_format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture: " << texture_file_path << std::endl;
    return -1;
  }
  stbi_image_free(data);
  return 0;
}

void ActiveTexture(const unsigned int* texture_ptr,
                   const unsigned int texture_idx = 0) {
  // Bind Textures
  glActiveTexture(GL_TEXTURE0 + texture_idx);
  glBindTexture(GL_TEXTURE_2D, *texture_ptr);
}

void BindVertices(const unsigned int* vao_ptr) { glBindVertexArray(*vao_ptr); }

void DrawVertices(const unsigned int vertices_size) {
  glDrawArrays(GL_TRIANGLES, 0, vertices_size / 8);
}

class Mesh {
 public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  void Build(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
             std::vector<Texture> textures) {
    // Generate, bind, set vertex array objects
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    // Generate vertex array / vertex array buffer / element array buffer object
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    // Bind vertex to array objects
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // Set pointer to array objects
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, tex_coords));

    // Free memory
    glBindVertexArray(0);
  }

  void Draw(Shader shader) {
    // Draw diverse textures in mesh elements
    unsigned int diffuse_count = 1, specular_count = 1, normal_count = 1;
    for (unsigned int idx = 0; idx < textures.size(); idx++) {
      // Set names of texture per types
      std::string texture_type = textures[idx].type;
      std::string idx_of_type;
      if (texture_type == "TEXTURE_DIFFUSE_")
        idx_of_type = std::to_string(diffuse_count++);
      else if (texture_type == "TEXTURE_SPECULAR_")
        idx_of_type = std::to_string(specular_count++);
      else if (texture_type == "TEXTURE_NORMAL_")
        idx_of_type = std::to_string(normal_count++);

      // Allocate uniform textures to texture units in texture sampler
      glActiveTexture(GL_TEXTURE0 + idx);
      shader.SetUniformInt_((texture_type + idx_of_type).c_str(), idx);
      glBindTexture(GL_TEXTURE_2D, textures[idx].id);
    }

    // Draw mesh elements
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
  }

 private:
  unsigned int vao_, vbo_, ebo_;
};
}  // namespace liqi

#endif  // LIQI_MESH_H_
