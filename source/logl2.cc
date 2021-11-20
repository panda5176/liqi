#include <liqi/main.h>
#include <liqi/model.h>
#include <liqi/shader.h>

const char* TITLE = "LOGL2";
const char* FONT_FILE_PATH = "asset/D2Coding.ttf";

const char* SUBJ_VERTEX_SHADER_FILE_PATH = "shader/logl2_subj.vert.glsl";
const char* SUBJ_FRAGMENT_SHADER_FILE_PATH = "shader/logl2_subj.frag.glsl";
const char* MARBLE_TEXTURE_FILE_PATH = "asset/marble.jpg";
const char* METAL_TEXTURE_FILE_PATH = "asset/metal.png";

const char* TRANSPARENT_VERTEX_SHADER_FILE_PATH =
    "shader/logl2_transparent.vert.glsl";
const char* TRANSPARENT_FRAGMENT_SHADER_FILE_PATH =
    "shader/logl2_transparent.frag.glsl";
const char* GRASS_TEXTURE_FILE_PATH = "asset/grass.png";

const char* BLEND_VERTEX_SHADER_FILE_PATH = "shader/logl2_blend.vert.glsl";
const char* BLEND_FRAGMENT_SHADER_FILE_PATH = "shader/logl2_blend.frag.glsl";
const char* WINDOW_TEXTURE_FILE_PATH = "asset/window.png";

const char* SKYBOX_VERTEX_SHADER_FILE_PATH = "shader/logl2_skybox.vert.glsl";
const char* SKYBOX_FRAGMENT_SHADER_FILE_PATH = "shader/logl2_skybox.frag.glsl";
std::vector<std::string> SKYBOX_TEXTURE_FILES_PATHS = {
    "asset/skybox/right.jpg", "asset/skybox/left.jpg",
    "asset/skybox/top.jpg",   "asset/skybox/bottom.jpg",
    "asset/skybox/front.jpg", "asset/skybox/back.jpg"};

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
    5.0f,  -0.5f, 5.0f,  0.0f, 1.0f, 0.0f, 2.0f, 0.0f,  // 1
    -5.0f, -0.5f, 5.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // 2
    -5.0f, -0.5f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f,  // 3
    5.0f,  -0.5f, 5.0f,  0.0f, 1.0f, 0.0f, 2.0f, 0.0f,  // 4
    -5.0f, -0.5f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f,  // 5
    5.0f,  -0.5f, -5.0f, 0.0f, 1.0f, 0.0f, 2.0f, 2.0f   // 6
};
const float GRASS_VERTICES[] = {
    0.0f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // 1
    0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // 2
    1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 3
    0.0f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // 4
    1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 5
    1.0f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // 6
};
float SKYBOX_VERTICES[] = {
    -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 1
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 2
    1.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 3
    1.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 4
    1.0f,  1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 5
    -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 6

    -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 1
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 2
    -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 3
    -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 4
    -1.0f, 1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 5
    -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 6

    1.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 1
    1.0f,  -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 2
    1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 3
    1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 4
    1.0f,  1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 5
    1.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 6

    -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 1
    -1.0f, 1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 2
    1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 3
    1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 4
    1.0f,  -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 5
    -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 6

    -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 1
    1.0f,  1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 2
    1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 3
    1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 4
    -1.0f, 1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 5
    -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 6

    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 1
    -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 2
    1.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 3
    1.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 4
    -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 5
    1.0f,  -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // 6
};
const glm::vec3 GRASS_POSITIONS[] = {
    glm::vec3(-1.5f, 0.0f, -0.48f), glm::vec3(1.5f, 0.0f, 0.51f),
    glm::vec3(0.0f, 0.0f, 0.7f), glm::vec3(-0.3f, 0.0f, -2.3f),
    glm::vec3(0.5f, 0.0f, -0.6f)};
const glm::vec3 WINDOW_POSITIONS[] = {
    glm::vec3(-1.5f, 0.0f, 0.52f), glm::vec3(1.5f, 0.0f, 1.51f),
    glm::vec3(0.0f, 0.0f, 1.7f), glm::vec3(-0.3f, 0.0f, -1.3f),
    glm::vec3(0.5f, 0.0f, 0.4f)};

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
glm::vec3 POINT_LIGHT_POSITIONS[] = {glm::vec3(2.0f, 0.5f, 1.0f)};

int main(const int argc, const char* argv[]) {
  // Create window
  liqi::Create(TITLE, FONT_FILE_PATH);

  // Build shaders
  liqi::Shader subj_shader, transparent_shader, blend_shader, skybox_shader;
  try {
    subj_shader.Build(SUBJ_VERTEX_SHADER_FILE_PATH,
                      SUBJ_FRAGMENT_SHADER_FILE_PATH);
    transparent_shader.Build(TRANSPARENT_VERTEX_SHADER_FILE_PATH,
                             TRANSPARENT_FRAGMENT_SHADER_FILE_PATH);
    blend_shader.Build(BLEND_VERTEX_SHADER_FILE_PATH,
                       BLEND_FRAGMENT_SHADER_FILE_PATH);
    skybox_shader.Build(SKYBOX_VERTEX_SHADER_FILE_PATH,
                        SKYBOX_FRAGMENT_SHADER_FILE_PATH);
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

  // Build transparent & blending vertices
  // Window vertices == Grass vertices
  unsigned int grass_vao, grass_vbo, window_vao, window_vbo;
  liqi::BuildVertices(&grass_vao, &grass_vbo, GRASS_VERTICES,
                      sizeof(GRASS_VERTICES));
  liqi::BuildVertices(&window_vao, &window_vbo, GRASS_VERTICES,
                      sizeof(GRASS_VERTICES));
  unsigned int grass_texture, window_texture;
  if (liqi::SetTexture(&grass_texture, GRASS_TEXTURE_FILE_PATH, true,
                       "clamp_edge") ||
      liqi::SetTexture(&window_texture, WINDOW_TEXTURE_FILE_PATH, false,
                       "clamp_edge")) {
    return -1;
  }

  // Build skybox
  unsigned int skybox_vao, skybox_vbo;
  liqi::BuildVertices(&skybox_vao, &skybox_vbo, SKYBOX_VERTICES,
                      sizeof(SKYBOX_VERTICES));
  unsigned int skybox_texture;
  liqi::LoadCubeMap(&skybox_texture, SKYBOX_TEXTURE_FILES_PATHS);

  // Render
  unsigned int n_point_lights =
      sizeof(POINT_LIGHT_POSITIONS) / sizeof(*POINT_LIGHT_POSITIONS);
  unsigned int n_grasses = sizeof(GRASS_POSITIONS) / sizeof(*GRASS_POSITIONS);
  while (liqi::Render()) {
    // Skybox
    glDepthFunc(GL_LEQUAL);
    skybox_shader.Use();
    skybox_shader.SetTransform(glm::mat4(glm::mat3(liqi::view_transform)),
                               liqi::proj_transform);
    liqi::BindVertices(&skybox_vao);
    liqi::ActiveTexture(&skybox_texture);
    liqi::DrawVertices(sizeof(SKYBOX_VERTICES));
    glDepthFunc(GL_LESS);

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

    // Subject 1 & 2
    liqi::BindVertices(&subj_vao);
    liqi::ActiveTexture(&subj_texture);
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
    liqi::ActiveTexture(&floor_texture);
    subj_shader.SetModel(glm::mat4(1.0f));
    liqi::DrawVertices(sizeof(FLOOR_VERTICES));

    // Transparent uniforms
    transparent_shader.Use();
    transparent_shader.SetCamPos(liqi::cam_pos);
    transparent_shader.SetMaterial(0, 1, SHININESS);
    transparent_shader.SetAttnConst(ATTN_CONST, ATTN_LIN, ATTN_QUAD);
    transparent_shader.SetDirLight(DIR_LIGHT_DIR, DIR_LIGHT_AMBIENT,
                                   DIR_LIGHT_DIFFUSE, DIR_LIGHT_SPECULAR);
    for (unsigned int idx = 0; idx < n_point_lights; idx++) {
      transparent_shader.SetPointLight(POINT_LIGHT_POSITIONS[idx],
                                       POINT_LIGHT_AMBIENT, POINT_LIGHT_DIFFUSE,
                                       POINT_LIGHT_SPECULAR, idx);
    }
    transparent_shader.SetSpotLight(
        liqi::cam_pos, liqi::cam_front, SPOT_LIGHT_AMBIENT, SPOT_LIGHT_DIFFUSE,
        SPOT_LIGHT_SPECULAR, FLASH_COS_PHI, FLASH_COS_GAMMA);
    transparent_shader.SetTransform(liqi::view_transform, liqi::proj_transform);

    // Grass
    liqi::BindVertices(&grass_vao);
    liqi::ActiveTexture(&grass_texture);
    for (unsigned int idx = 0; idx < n_grasses; idx++) {
      model_transform = glm::translate(glm::mat4(1.0f), GRASS_POSITIONS[idx]);
      transparent_shader.SetModel(model_transform);
      liqi::DrawVertices(sizeof(GRASS_VERTICES));
    }

    // Blending uniforms
    blend_shader.Use();
    blend_shader.SetCamPos(liqi::cam_pos);
    blend_shader.SetMaterial(0, 1, SHININESS);
    blend_shader.SetAttnConst(ATTN_CONST, ATTN_LIN, ATTN_QUAD);
    blend_shader.SetDirLight(DIR_LIGHT_DIR, DIR_LIGHT_AMBIENT,
                             DIR_LIGHT_DIFFUSE, DIR_LIGHT_SPECULAR);
    for (unsigned int idx = 0; idx < n_point_lights; idx++) {
      blend_shader.SetPointLight(POINT_LIGHT_POSITIONS[idx],
                                 POINT_LIGHT_AMBIENT, POINT_LIGHT_DIFFUSE,
                                 POINT_LIGHT_SPECULAR, idx);
    }
    blend_shader.SetSpotLight(
        liqi::cam_pos, liqi::cam_front, SPOT_LIGHT_AMBIENT, SPOT_LIGHT_DIFFUSE,
        SPOT_LIGHT_SPECULAR, FLASH_COS_PHI, FLASH_COS_GAMMA);
    blend_shader.SetTransform(liqi::view_transform, liqi::proj_transform);

    // Window
    // n_windows == n_grasses
    liqi::BindVertices(&window_vao);
    liqi::ActiveTexture(&window_texture);
    std::map<float, glm::vec3> sorted_windows;
    for (unsigned int idx = 0; idx < n_grasses; idx++) {
      float distance = glm::length(liqi::cam_pos - WINDOW_POSITIONS[idx]);
      sorted_windows[distance] = WINDOW_POSITIONS[idx];
    }
    for (std::map<float, glm::vec3>::reverse_iterator iterator =
             sorted_windows.rbegin();
         iterator != sorted_windows.rend(); ++iterator) {
      model_transform = glm::translate(glm::mat4(1.0f), iterator->second);
      transparent_shader.SetModel(model_transform);
      liqi::DrawVertices(sizeof(GRASS_VERTICES));
    }
  }

  // Destroy window
  liqi::Destroy();
  return 0;
}
