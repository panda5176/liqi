#ifndef LIQI_WINDOW_H_
#define LIQI_WINDOW_H_

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

namespace liqi {
namespace private_ {
// Private =====================================================================
// Window
GLFWwindow* window_ = nullptr;
unsigned int window_width_ = 1600, window_height_ = 900;
bool is_first_frame_ = true;
bool do_show_option_window_ = false;
ImGuiIO option_io_ = ImGuiIO{};

// Cursor
bool do_initialize_cursor_ = true;
float cursor_last_x_ = window_width_ / 2.0f,
      cursor_last_y_ = window_height_ / 2.0f;
float sensitivity_ = 0.1f;
float cursor_before_option_x_ = 0.0f, cursor_before_option_y_ = 0.0f;

// Key
bool had_escape_key_pressed_ = false, had_escape_key_released_ = true;

// Camera
float yaw_ = -90.0f, pitch_ = 0.0f;
float fov_ = 45.0f, fov_min_ = 15.0f, fov_max_ = 60.0f;
float cam_speed_unit_ = 2.5f;
float current_frame_ = 0.0f, last_frame_ = 0.0f, delta_time_ = 0.0f;
glm::vec3 cam_pos_ = glm::vec3(0.0f, 0.0f, 3.0f),
          cam_front_ = glm::vec3(0.0f, 0.0f, -1.0f),
          cam_up_ = glm::vec3(0.0f, 1.0f, 0.0f);
}  // namespace private_

// Public ======================================================================
glm::vec3 cam_pos = glm::vec3(0.0f), cam_front = glm::vec3(0.0f),
          cam_up = glm::vec3(0.0f);
glm::mat4 view_transform = glm::mat4(0.0f), proj_transform = glm::mat4(0.0f);
float current_frame = 0.0f;

namespace private_ {
// Private =====================================================================
void FramebufferSizeCallback_(GLFWwindow* window, const int new_window_width,
                              const int new_window_height) {
  // Set window size
  glViewport(0, 0, new_window_width, new_window_height);
  private_::window_width_ = new_window_width;
  private_::window_height_ = new_window_height;
}

void CursorPosCallback_(GLFWwindow* window, const double cursor_x,
                        const double cursor_y) {
  // Callback function for cursor movement catch
  // Initialize cursor
  if (private_::do_initialize_cursor_) {
    private_::cursor_last_x_ = cursor_x;
    private_::cursor_last_y_ = cursor_y;
    private_::do_initialize_cursor_ = false;
  }

  // Calculate new yaw and pitch from cursor movement
  private_::yaw_ +=
      (cursor_x - private_::cursor_last_x_) * private_::sensitivity_;
  private_::pitch_ +=
      (private_::cursor_last_y_ - cursor_y) * private_::sensitivity_;
  private_::cursor_last_x_ = cursor_x;
  private_::cursor_last_y_ = cursor_y;

  // Pitch range restriction
  if (private_::pitch_ > 89.0f)
    private_::pitch_ = 89.0f;
  else if (private_::pitch_ < -89.0f)
    private_::pitch_ = -89.0f;

  // Calculate new camera front from new yaw and pitch
  glm::vec3 new_front;
  new_front.x = std::cos(glm::radians(private_::yaw_)) *
                std::cos(glm::radians(private_::pitch_));
  new_front.y = std::sin(glm::radians(private_::pitch_));
  new_front.z = std::sin(glm::radians(private_::yaw_)) *
                std::cos(glm::radians(private_::pitch_));
  private_::cam_front_ = glm::normalize(new_front);
  cam_front = private_::cam_front_;
}

void ScrollCallback_(GLFWwindow* window, const double scroll_x,
                     const double scroll_y) {
  // Callback function for scrool movement catch
  if (private_::fov_ >= private_::fov_min_ &&
      private_::fov_ <= private_::fov_max_)
    private_::fov_ -= scroll_y;
  else if (private_::fov_ < private_::fov_min_)
    private_::fov_ = private_::fov_min_;
  else if (private_::fov_ > private_::fov_max_)
    private_::fov_ = private_::fov_max_;
}

void ProcessInput_(const float cam_speed) {
  // Camera movement
  if (glfwGetKey(private_::window_, GLFW_KEY_W) == GLFW_PRESS)
    private_::cam_pos_ += cam_speed * private_::cam_front_;
  if (glfwGetKey(private_::window_, GLFW_KEY_S) == GLFW_PRESS)
    private_::cam_pos_ -= cam_speed * private_::cam_front_;
  if (glfwGetKey(private_::window_, GLFW_KEY_A) == GLFW_PRESS)
    private_::cam_pos_ -=
        cam_speed *
        glm::normalize(glm::cross(private_::cam_front_, private_::cam_up_));
  if (glfwGetKey(private_::window_, GLFW_KEY_D) == GLFW_PRESS)
    private_::cam_pos_ +=
        cam_speed *
        glm::normalize(glm::cross(private_::cam_front_, private_::cam_up_));
  cam_pos = private_::cam_pos_;
}

void ExitOptionWindow_() {
  // Exit option window
  glfwSetCursorPos(private_::window_, private_::cursor_before_option_x_,
                   private_::cursor_before_option_y_);
  glfwSetInputMode(private_::window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(private_::window_, private_::CursorPosCallback_);
  glfwSetScrollCallback(private_::window_, private_::ScrollCallback_);
  private_::do_show_option_window_ = false;
}

int SetOptionWindow_() {
  // Set option window
  ImGui::Begin("Options");
  if (ImGui::Button("Exit Options")) {
    ExitOptionWindow_();
  }
  ImGui::SameLine();
  if (ImGui::Button("Exit Program")) {
    glfwSetWindowShouldClose(private_::window_, true);
    return !glfwWindowShouldClose(private_::window_);
  }
  ImGui::SliderFloat("Camera speed", &private_::cam_speed_unit_, 0.0f, 10.0f,
                     "%.1f", ImGuiSliderFlags_AlwaysClamp);
  ImGui::End();
  return 1;
}

void ControlOptionWindow_() {
  // Control option window when escape key is pressured
  if (private_::had_escape_key_pressed_ &&
      glfwGetKey(private_::window_, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
    private_::had_escape_key_released_ = true;
    private_::had_escape_key_pressed_ = false;
  }

  if (private_::had_escape_key_released_ &&
      glfwGetKey(private_::window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    private_::had_escape_key_pressed_ = true;
    private_::had_escape_key_released_ = false;

    if (private_::do_show_option_window_) {
      ExitOptionWindow_();
    } else {
      private_::cursor_before_option_x_ = private_::cursor_last_x_;
      private_::cursor_before_option_y_ = private_::cursor_last_y_;
      glfwSetInputMode(private_::window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      glfwSetCursorPosCallback(private_::window_, NULL);
      glfwSetScrollCallback(private_::window_, NULL);
      glfwSetCursorPos(private_::window_, private_::window_width_ / 2.0,
                       private_::window_height_ / 2.0);
      private_::do_show_option_window_ = true;
    }
  }
}
}  // namespace private_

// Public ======================================================================
void Create(const char* title, const char* font_file_path) {
  // Create window
  // Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // GLFW version declaration
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Only core
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // in MacOS
#endif

  // Set window
  private_::window_ = glfwCreateWindow(
      private_::window_width_, private_::window_height_, title, NULL, NULL);
  glfwMakeContextCurrent(private_::window_);

  // Set option window
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  private_::option_io_ = ImGui::GetIO();
  (void)private_::option_io_;
  private_::option_io_.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  private_::option_io_.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(private_::window_, true);
  ImGui_ImplOpenGL3_Init("#version 330");
  ImFont* option_font =
      private_::option_io_.Fonts->AddFontFromFileTTF(font_file_path, 18.0f);
  if (!option_font) throw 1;

  // Initialize GLAD, after window setting
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  // Detect window size change
  glfwSetFramebufferSizeCallback(private_::window_,
                                 private_::FramebufferSizeCallback_);

  // Capture cursor in window
  glfwSetInputMode(private_::window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Call callback functions when cursor position & scroll change
  glfwSetCursorPosCallback(private_::window_, private_::CursorPosCallback_);
  glfwSetScrollCallback(private_::window_, private_::ScrollCallback_);

  // Enable Z-buffer test
  glEnable(GL_DEPTH_TEST);

  // Flip y-axis of texture when loading
  stbi_set_flip_vertically_on_load(true);
}

bool Render() {
  if (!private_::is_first_frame_) {
    // Start option frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Show option window
    if (private_::do_show_option_window_) {
      if (!private_::SetOptionWindow_())
        return !glfwWindowShouldClose(private_::window_);
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap to rendered color buffers
    glfwSwapBuffers(private_::window_);

    // Check all occured events and update window
    glfwPollEvents();
  }
  private_::is_first_frame_ = false;
  private_::ControlOptionWindow_();

  // Process input with delta time
  private_::current_frame_ = glfwGetTime();
  private_::delta_time_ = private_::current_frame_ - private_::last_frame_;
  private_::last_frame_ = private_::current_frame_;
  const float cam_speed = private_::cam_speed_unit_ * private_::delta_time_;
  if (!private_::do_show_option_window_) private_::ProcessInput_(cam_speed);

  // Initialize color at each frame
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Give changed variables
  view_transform =
      glm::lookAt(private_::cam_pos_, private_::cam_pos_ + private_::cam_front_,
                  private_::cam_up_);
  proj_transform = glm::perspective(
      glm::radians(private_::fov_),
      (float)private_::window_width_ / private_::window_height_, 0.1f, 100.0f);
  current_frame = private_::current_frame_;

  return !glfwWindowShouldClose(private_::window_);
}

void Destroy() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
}
}  // namespace liqi

#endif  // LIQI_WINDOW_H_
