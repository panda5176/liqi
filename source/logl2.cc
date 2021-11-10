#include <liqi/main.h>
#include <liqi/model.h>
#include <liqi/shader.h>

const char* TITLE = "LOGL2";
const char* FONT_FILE_PATH = "asset/D2Coding.ttf";

const char* SUBJ_VERTEX_SHADER_FILE_PATH = "shader/logl2_subj.vert.glsl";
const char* SUBJ_FRAGMENT_SHADER_FILE_PATH = "shader/logl2_subj.frag.glsl";
const char* MARBLE_TEXTURE_FILE_PATH = "asset/marble.jpg";
const char* METAL_TEXTURE_FILE_PATH = "asset/metal.png";

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
const float FLOOR_VERTICES[] = {
    5.0f,  -0.5f, 5.0f,  1.0f, 0.0f, 0.0f, 2.0f, 0.0f,  // 1
    -5.0f, -0.5f, 5.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 2
    -5.0f, -0.5f, -5.0f, 1.0f, 0.0f, 0.0f, 0.0f, 2.0f,  // 3
    5.0f,  -0.5f, 5.0f,  1.0f, 0.0f, 0.0f, 2.0f, 0.0f,  // 4
    -5.0f, -0.5f, -5.0f, 1.0f, 0.0f, 0.0f, 0.0f, 2.0f,  // 5
    5.0f,  -0.5f, -5.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f   // 6
};

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
  liqi::Create(TITLE, FONT_FILE_PATH);

  // Build shaders
  liqi::Shader subj_shader, floor_shader;
  try {
    subj_shader.Build(SUBJ_VERTEX_SHADER_FILE_PATH,
                      SUBJ_FRAGMENT_SHADER_FILE_PATH);
  } catch (unsigned char error_code) {
    std::cout << "Failed to build shader program for subject" << std::endl;
    return error_code;
  }

  // Build subject vertices
  unsigned int subj_vao, subj_vbo, floor_vao, floor_vbo;
  liqi::BuildVertices(&subj_vao, &subj_vbo, SUBJ_VERTICES,
                      sizeof(SUBJ_VERTICES));
  liqi::BuildVertices(&floor_vao, &floor_vbo, FLOOR_VERTICES,
                      sizeof(FLOOR_VERTICES));
  unsigned int subj_texture, floor_texture;
  if (liqi::SetTexture(&subj_texture, MARBLE_TEXTURE_FILE_PATH) ||
      liqi::SetTexture(&floor_texture, METAL_TEXTURE_FILE_PATH)) {
    return -1;
  }

  // Render
  unsigned int n_point_lights =
      sizeof(POINT_LIGHT_POSITIONS) / sizeof(*POINT_LIGHT_POSITIONS);
  while (liqi::Render()) {
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
    liqi::ActiveTexture(&floor_texture, 1);

    // Subject 1 & 2
    liqi::BindVertices(&subj_vao);
    glm::mat4 model_transform = glm::mat4(1.0f);
    model_transform =
        glm::translate(model_transform, glm::vec3(-1.0f, 0.0f, -1.0f));
    subj_shader.SetModel(model_transform);
    liqi::DrawVertices(sizeof(SUBJ_VERTICES));
    model_transform = glm::mat4(1.0f);
    model_transform =
        glm::translate(model_transform, glm::vec3(2.0f, 0.0f, 0.0f));
    subj_shader.SetModel(model_transform);
    liqi::DrawVertices(sizeof(SUBJ_VERTICES));

    // Floor
    liqi::BindVertices(&floor_vao);
    subj_shader.SetModel(glm::mat4(1.0f));
    liqi::DrawVertices(sizeof(FLOOR_VERTICES));
  }

  // Destroy window
  liqi::Destroy();
  return 0;
}
