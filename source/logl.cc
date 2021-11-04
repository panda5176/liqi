#include <liqi/model.h>
#include <liqi/shader.h>
#include <liqi/window.h>

const char* TITLE = "LOGL";

const char* OBJ_VERTEX_SHADER_FILE_PATH = "shader/logl_obj.vert.glsl";
const char* OBJ_FRAGMENT_SHADER_FILE_PATH = "shader/logl_obj.frag.glsl";
const char* OBJ_FILE_PATH = "asset/backpack/backpack.obj";

const char* SUBJ_VERTEX_SHADER_FILE_PATH = "shader/logl_subj.vert.glsl";
const char* SUBJ_FRAGMENT_SHADER_FILE_PATH = "shader/logl_subj.frag.glsl";
const char* SUBJ_TEXTURE_FILE_PATH = "asset/container.png";
const char* SUBJ_SPECULAR_FILE_PATH = "asset/container_specular.png";

const float SUBJ_VERTICES[] = {
    // With normals and texture coordinates
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  // 1-1
    0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,  // 1-2
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,  // 1-3
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,  // 1-4
    -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f,  // 1-5
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  // 1-6

    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // 2-1
    0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  // 2-2
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  // 2-3
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  // 2-4
    -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  // 2-5
    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // 2-6

    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  // 3-1
    -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f,  // 3-2
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  // 3-3
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  // 3-4
    -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  // 3-5
    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  // 3-6

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // 4-1
    0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // 4-2
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // 4-3
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // 4-4
    0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // 4-5
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // 4-6

    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,  // 5-1
    0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,  // 5-2
    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,  // 5-3
    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,  // 5-4
    -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 0.0f,  // 5-5
    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,  // 5-6

    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // 6-1
    0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  // 6-2
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // 6-3
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // 6-4
    -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  // 6-5
    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f   // 6-6
};
glm::vec3 SUBJ_POSITIONS[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

const float SHININESS = 64.0f;
const glm::vec3 DIR_LIGHT_DIR = glm::vec3(-0.2f, -1.0f, -0.3f),
                DIR_LIGHT_AMBIENT = glm::vec3(0.05f, 0.05f, 0.05f),
                DIR_LIGHT_DIFFUSE = glm::vec3(0.4f, 0.4f, 0.4f),
                DIR_LIGHT_SPECULAR = glm::vec3(0.5f, 0.5f, 0.5f);
const glm::vec3 POINT_LIGHT_AMBIENT = glm::vec3(0.05f, 0.05f, 0.05f),
                POINT_LIGHT_DIFFUSE = glm::vec3(0.8f, 0.8f, 0.8f),
                POINT_LIGHT_SPECULAR = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 SPOT_LIGHT_AMBIENT = glm::vec3(0.0f, 0.0f, 0.0f),
                SPOT_LIGHT_DIFFUSE = glm::vec3(1.0f, 1.0f, 1.0f),
                SPOT_LIGHT_SPECULAR = glm::vec3(1.0f, 1.0f, 1.0f);
const float ATTN_CONST = 1.0f, ATTN_LIN = 0.09f, ATTN_QUAD = 0.032f;
const float FLASH_COS_PHI = 12.5f, FLASH_COS_GAMMA = 17.5f;
glm::vec3 POINT_LIGHT_POSITIONS[] = {
    glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.0f, 0.0f, -3.0f)};

int main(const int argc, const char* argv[]) {
  // Create window
  liqi::Create(TITLE);

  // Build shaders
  liqi::Shader obj_shader, subj_shader;
  try {
    obj_shader.Build(OBJ_VERTEX_SHADER_FILE_PATH,
                     OBJ_FRAGMENT_SHADER_FILE_PATH);
  } catch (unsigned char error_code) {
    std::cout << "Failed to build shader program for object" << std::endl;
    return error_code;
  }
  try {
    subj_shader.Build(SUBJ_VERTEX_SHADER_FILE_PATH,
                      SUBJ_FRAGMENT_SHADER_FILE_PATH);
  } catch (unsigned char error_code) {
    std::cout << "Failed to build shader program for subject" << std::endl;
    return error_code;
  }

  // Build object model
  liqi::Model model;
  model.Build(OBJ_FILE_PATH);

  // Build subject vertices
  unsigned int subj_vao, subj_vbo;
  liqi::BuildVertices(&subj_vao, &subj_vbo, SUBJ_VERTICES,
                      sizeof(SUBJ_VERTICES));
  unsigned int subj_texture, subj_specular_texture;
  if (liqi::SetTexture(&subj_texture, SUBJ_TEXTURE_FILE_PATH, GL_RGBA) ||
      liqi::SetTexture(&subj_specular_texture, SUBJ_SPECULAR_FILE_PATH,
                       GL_RGBA)) {
    return -1;
  }

  // Render
  unsigned int n_point_lights =
      sizeof(POINT_LIGHT_POSITIONS) / sizeof(*POINT_LIGHT_POSITIONS);
  unsigned int n_subjs = sizeof(SUBJ_POSITIONS) / sizeof(*SUBJ_POSITIONS);
  while (liqi::Render()) {
    glm::mat4 model_transform = glm::mat4(1.0f);
    model_transform =
        glm::translate(model_transform, glm::vec3(0.0f, 0.0f, -10.0f));
    model_transform = glm::scale(model_transform, glm::vec3(1.0f, 1.0f, 1.0f));

    // Set uniforms for object
    obj_shader.Use();
    obj_shader.SetCamPos(liqi::cam_pos);
    obj_shader.SetShininess(SHININESS);
    obj_shader.SetAttnConst(ATTN_CONST, ATTN_LIN, ATTN_QUAD);
    obj_shader.SetDirLight(DIR_LIGHT_DIR, DIR_LIGHT_AMBIENT, DIR_LIGHT_DIFFUSE,
                           DIR_LIGHT_SPECULAR);
    for (unsigned int idx = 0; idx < n_point_lights; idx++) {
      obj_shader.SetPointLight(POINT_LIGHT_POSITIONS[idx], POINT_LIGHT_AMBIENT,
                               POINT_LIGHT_DIFFUSE, POINT_LIGHT_SPECULAR, idx);
    }
    obj_shader.SetSpotLight(liqi::cam_pos, liqi::cam_front, SPOT_LIGHT_AMBIENT,
                            SPOT_LIGHT_DIFFUSE, SPOT_LIGHT_SPECULAR,
                            FLASH_COS_PHI, FLASH_COS_GAMMA);
    obj_shader.SetTransform(liqi::view_transform, liqi::proj_transform,
                            model_transform);

    // Draw object model
    model.Draw(obj_shader);

    // Set uniforms for subject
    subj_shader.Use();
    subj_shader.SetCamPos(liqi::cam_pos);
    subj_shader.SetMaterial(0, 1, SHININESS);
    subj_shader.SetAttnConst(ATTN_CONST, ATTN_LIN, ATTN_QUAD);
    subj_shader.SetDirLight(DIR_LIGHT_DIR, DIR_LIGHT_AMBIENT, DIR_LIGHT_DIFFUSE,
                            DIR_LIGHT_SPECULAR);
    for (unsigned int idx = 0; idx < n_point_lights; idx++) {
      subj_shader.SetPointLight(POINT_LIGHT_POSITIONS[idx], POINT_LIGHT_AMBIENT,
                                POINT_LIGHT_DIFFUSE, POINT_LIGHT_SPECULAR, idx);
    }
    subj_shader.SetSpotLight(liqi::cam_pos, liqi::cam_front, SPOT_LIGHT_AMBIENT,
                             SPOT_LIGHT_DIFFUSE, SPOT_LIGHT_SPECULAR,
                             FLASH_COS_PHI, FLASH_COS_GAMMA);
    subj_shader.SetTransform(liqi::view_transform, liqi::proj_transform);

    // Draw subject model
    liqi::ActiveTexture(&subj_texture, 0);
    liqi::ActiveTexture(&subj_specular_texture, 1);
    liqi::BindVertices(&subj_vao);
    for (unsigned int idx = 0; idx < n_subjs; idx++) {
      model_transform = glm::mat4(1.0f);
      model_transform = glm::translate(model_transform, SUBJ_POSITIONS[idx]);
      model_transform =
          glm::rotate(model_transform, glm::radians(20.0f * idx),
                      glm::vec3(1.0f, 0.3f, 0.5f));  // various angles
      model_transform = glm::rotate(
          model_transform, (float)liqi::current_frame * glm::radians(50.0f),
          glm::vec3(0.5f, 1.0f, 0.0f));
      subj_shader.SetModel(model_transform);
      liqi::DrawVertices(sizeof(SUBJ_VERTICES));
    }
  }

  // Destroy window
  liqi::Destroy();
  return 0;
}
