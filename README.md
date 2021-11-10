# LIQI

## Dependencies
- [GLFW](https://www.glfw.org): An OpenGL library
- [GLAD](https://glad.dav1d.de): Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs
- [GLM](https://github.com/g-truc/glm): OpenGL Mathematics
- [STB](https://github.com/nothings/stb): Single-file public domain libraries for C/C++
- [ASSIMP](http://assimp.org/index.php/downloads): The Open-Asset-Importer-Lib
- [Dear ImGui](https://github.com/ocornut/imgui): Bloat-free Graphical User interface for C++ with minimal dependencies

## How to compile
```bash
# Make include folder
mkdir ./include

# GLFW
## Download GLFW from https://www.glfw.org to ${glfw_folder}
## Compile & Build
cmake -S ${glfw_folder} -B ${glfw_bulid_folder}
make -C ${glfw_bulid_folder}
## Copy libraries
cp -r ${glfw_folder}/include/* ./include/
cp ${glfw_bulid_folder}/src/libglfw3.a ${glfw_bulid_folder}/src/glfw3.dll ./library/

# GLAD
## Download GLAD from https://glad.dav1d.de and unzip to ${glad_folder}
## Copy libraries
cp -r ${glad_folder}/include/* ./include/
cp ${glad_folder}/src/glad.c ./include/glad/
## Compile
g++ -c ./include/glad/glad.c -o ./include/glad/glad.o -I ./include/

# GLM
## Download GLM from https://github.com/g-truc/glm and unzip to ${glm_folder}
## Copy libraries
cp -r ${glm_folder}/glm ./include/

# STB
## Download STB from https://github.com/nothings/stb and unzip to ${stb_folder}
## Make include folder
mkdir ./include/stb
## Copy libraries
cp ${stb_folder}/stb_image.h ./include/

# ASSIMP
## WARNING: Currently Assimp >= v5.0 cannot be compiled with MINGW Makefiles
## Download ASSIMP from http://assimp.org/index.php/downloads and unzip to ${assimp_folder}
## Compile & Build
cmake -S ${assimp_folder} -B ${assimp_bulid_folder}
## Copy libraries
cp -r ${assimp_folder}/include/* ./include/
cp ${assimp_build_folder}/include/* ./include/
cp ${assimp_build_folder}/lib/* ./library/
cp ${assimp_build_folder}/bin/*.dll ./

# Dear ImGui
## Download Dear ImGui from https://github.com/ocornut/imgui/releases/ and unzip to ${imgui_folder}
## Make include folder
mkdir ./include/imgui
## Copy libraries
## WARNING: Exclude `${imgui_folder}/imgui_demo.cpp`
cp ${imgui_folder}/*.h ${imgui_folder}/*.cpp ./include/imgui/
cp ${imgui_folder}/backends/*_glfw* ${imgui_folder}/backends/*_opengl3* ./include/imgui/
## Compile
cd ./include/imgui
g++ -c ./*.c -I ../
cd ../..

# Compile & Build
## -O3 optimize for the faster execution
g++ -c ${source_file} -o ${object_file} -I ./include -O3
## WARNING: ${output_file} must be at the same folder with ./shader and ./asset
g++ ${object_file} ./include/glad/glad.o ./include/imgui/*.o -o ${output_file} -L ./library/ -lmingw32 -lglfw3 -lopengl32 -lgdi32 -luser32 -lassimp
```

## Examples in `./source/`
### Make with `./CMakeLists.txt`
- [LOGL](source\logl.cc): Learnings from [LearnOpenGL](https://learnopengl.com)
- [LOGL2](source\logl2.cc): Learnings from [LearnOpenGL](https://learnopengl.com)