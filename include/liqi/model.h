#ifndef LIQI_MODEL_H_
#define LIQI_MODEL_H_

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
#include <liqi/mesh.h>
#include <liqi/shader.h>

namespace liqi {
unsigned int LoadTextureFromFile(const std::string file_path) {
  // Load texture from texture file path
  unsigned int texture;
  glGenTextures(1, &texture);

  int width, height, components_count;
  unsigned char *data =
      stbi_load(file_path.c_str(), &width, &height, &components_count, 0);
  if (data) {
    GLenum format;
    if (components_count == 1)
      format = GL_RED;
    else if (components_count == 3)
      format = GL_RGB;
    else if (components_count == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << file_path << std::endl;
    stbi_image_free(data);
  }

  return texture;
}

class Model {
 public:
  void Build(const char *file_path) {
    // Load model from file using assimp
    std::string path = file_path;
    Assimp::Importer importer;
    directory_ = path.substr(0, path.find_last_of('/'));

    // Primitive shapes to triangles & texture coordinates flips on the y-axis
    const aiScene *scene =
        importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
      std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
      return;
    }

    ProcessNode_(scene->mRootNode, scene);  // Process root node
  }

  void Draw(Shader shader) {
    for (unsigned int idx = 0; idx < meshes_.size(); idx++)
      meshes_[idx].Draw(shader);
  }

 private:
  std::vector<Mesh> meshes_;
  std::vector<Texture> textures_;
  std::string directory_;

  void ProcessNode_(aiNode *node, const aiScene *scene) {
    // Process node recursively
    for (unsigned int idx = 0; idx < node->mNumMeshes; idx++) {
      // Scene mesh, index storaged in node
      aiMesh *mesh = scene->mMeshes[node->mMeshes[idx]];
      meshes_.push_back(ProcessMesh_(mesh, scene));
    }

    // For all child nodes
    for (unsigned int idx = 0; idx < node->mNumChildren; idx++) {
      ProcessNode_(node->mChildren[idx], scene);
    }
  }

  Mesh ProcessMesh_(aiMesh *mesh, const aiScene *scene) {
    // Process mesh at each node
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Get vertex data, consist of position, normal, and one texture coordinate
    for (unsigned int idx = 0; idx < mesh->mNumVertices; idx++) {
      Vertex vertex;

      aiVector3D position = mesh->mVertices[idx];
      vertex.position = glm::vec3(position.x, position.y, position.z);

      aiVector3D normal = mesh->mNormals[idx];
      vertex.normal = glm::vec3(normal.x, normal.y, normal.z);

      vertex.tex_coords = glm::vec2(0.0f, 0.0f);
      if (mesh->mTextureCoords[0]) {
        aiVector3D tex_coords = mesh->mTextureCoords[0][idx];
        vertex.tex_coords = glm::vec2(tex_coords.x, tex_coords.y);
      }

      vertices.push_back(vertex);
    }

    // Get index data from each face at each mesh
    for (unsigned int face_idx = 0; face_idx < mesh->mNumFaces; face_idx++) {
      aiFace face = mesh->mFaces[face_idx];
      for (unsigned int index_idx = 0; index_idx < face.mNumIndices;
           index_idx++)
        indices.push_back(face.mIndices[index_idx]);
    }

    // Get material data from scene, index storaged in mesh
    if (mesh->mMaterialIndex >= 0) {
      aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

      std::vector<Texture> diffuse_maps =
          LoadLightMaps_(material, aiTextureType_DIFFUSE, "TEXTURE_DIFFUSE_");
      textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

      std::vector<Texture> specular_maps =
          LoadLightMaps_(material, aiTextureType_SPECULAR, "TEXTURE_SPECULAR_");
      textures.insert(textures.end(), specular_maps.begin(),
                      specular_maps.end());

      std::vector<Texture> normal_maps =
          LoadLightMaps_(material, aiTextureType_HEIGHT, "TEXTURE_NORMAL_");
      textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
    }

    Mesh processed_mesh = Mesh();
    processed_mesh.Build(vertices, indices, textures);
    return processed_mesh;
  }

  std::vector<Texture> LoadLightMaps_(aiMaterial *material,
                                      aiTextureType texture_type,
                                      std::string texture_name) {
    // Load light maps from texture file
    std::vector<Texture> light_maps;
    for (unsigned int texture_idx = 0;
         texture_idx < material->GetTextureCount(texture_type); texture_idx++) {
      aiString file_name;
      const char *file_name_char = file_name.C_Str();
      bool do_skip = false;
      material->GetTexture(texture_type, texture_idx, &file_name);

      // Check if texture was already loaded
      for (unsigned int loaded_texture_idx = 0;
           loaded_texture_idx < textures_.size(); loaded_texture_idx++) {
        Texture texture_loaded = textures_[loaded_texture_idx];
        if (!std::strcmp(file_name_char, texture_loaded.path.data())) {
          light_maps.push_back(texture_loaded);
          do_skip = true;
          break;
        }
      }

      // Skip already loaded texture, whose path was saved
      if (!do_skip) {
        Texture texture;
        std::string file_path = directory_ + '/' + file_name_char;
        texture.id = LoadTextureFromFile(file_path);
        texture.type = texture_name;
        texture.path = file_name_char;
        light_maps.push_back(texture);
        textures_.push_back(texture);
      }
    }

    return light_maps;
  }
};
}  // namespace liqi

#endif  // LIQI_MODEL_H_
