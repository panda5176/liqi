cmake_minimum_required(VERSION 3.12)

project(
  liqi
  VERSION 0.1.0
  DESCRIPTION "Liqi Renderer"
  HOMEPAGE_URL https://github.com/panda5176/liqi
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

set(LOGL logl)
file(GLOB SRC source/logl.cc)
file(GLOB GLAD include/glad/glad.o)
file(GLOB IMGUI include/imgui/*.o)
add_executable(${LOGL} ${SRC} ${GLAD} ${IMGUI})
target_include_directories(${LOGL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_directories(${LOGL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/library)
target_link_libraries(${LOGL} PUBLIC mingw32 glfw3 opengl32 gdi32 user32 assimp)

set(LOGL2 logl2)
file(GLOB SRC source/logl2.cc)
file(GLOB GLAD include/glad/glad.o)
file(GLOB IMGUI include/imgui/*.o)
add_executable(${LOGL2} ${SRC} ${GLAD} ${IMGUI})
target_include_directories(${LOGL2} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_directories(${LOGL2} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/library)
target_link_libraries(${LOGL2} PUBLIC mingw32 glfw3 opengl32 gdi32 user32 assimp)
