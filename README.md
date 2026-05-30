# LearnGLES

An Android application demonstrating various OpenGL ES 3.0+ techniques, from basic rendering to advanced physically based rendering (PBR) and post-processing effects. This project is inspired by [LearnOpenGL](https://learnopengl.com/) but tailored for the Android platform using Kotlin for the UI and C++ for the high-performance rendering logic.

## 🚀 Features

The project is organized into several categories, each containing multiple tutorials:

### 🟢 Basic Techniques
- **Basic GLES**: Introduction to shaders, textures, and transformations.
- **Model Loading**: Loading complex 3D models using Assimp.
- **Cubemaps**: Skyboxes and environment mapping.
- **Instancing**: Efficiently rendering many instances of the same object (e.g., asteroids).
- **Blending & Depth/Stencil Testing**: Handling transparency and complex visibility.
- **Geometry & Tessellation Shaders**: Dynamic mesh modification on the GPU.
- **MSAA**: Multi-sample anti-aliasing for smoother edges.
- **Text Rendering**: Rendering high-quality text using FreeType or signed distance fields.
- **Frustum Culling**: Optimizing performance by only rendering visible objects.
- **Skeletal Animation**: Realistic character movement using bone-based animation.

### 💡 Lighting & Post-Processing
- **Basic Lighting**: Phong and Blinn-Phong lighting models.
- **Multiple Lights**: Handling various light types (directional, point, spotlights).
- **Shadow Mapping**: Real-time shadow generation.
- **Gamma Correction & HDR**: Improving color accuracy and dynamic range.
- **Bloom**: Simulating the glow effect for bright lights.
- **SSAO**: Screen-space ambient occlusion for realistic contact shadows.
- **Area Lights**: Simulating light from rectangular sources.

### 💎 Physically Based Rendering (PBR)
- **PBR Theory**: Implementation of the Cook-Torrance BRDF.
- **PBR Textures**: Using albedo, normal, metallic, roughness, and AO maps.
- **IBL (Image Based Lighting)**: Realistic environment lighting using HDR maps.
- **Normal & Parallax Mapping**: Adding fine surface details without increasing polygon count.

### 🔥 Advanced Techniques
- **Cascaded Shadow Maps (CSM)**: High-quality shadows for large-scale scenes.
- **Order Independent Transparency (OIT)**: Accurate rendering of overlapping transparent objects.
- **Direct State Access (DSA)**: Modern OpenGL techniques for better performance and cleaner code.

## 🛠 Tech Stack

- **Platform**: Android
- **Language**: Kotlin (UI), C++ (Rendering)
- **UI Framework**: Jetpack Compose
- **Graphics API**: OpenGL ES 3.0+
- **Build System**: Gradle with CMake for C++
- **Key Libraries**:
  - [Assimp](https://github.com/assimp/assimp): 3D model loading.
  - [GLM](https://github.com/g-truc/glm): OpenGL Mathematics.
  - [stb_image](https://github.com/nothings/stb): Image loading.
  - [free_type](https://gitlab.freedesktop.org/freetype/freetype): Font Rendering

## 📁 Project Structure

- `tutorial/src/main/java`: Kotlin source code for Android Activities and Compose UI.
- `tutorial/src/main/cpp`: C++ source code for the OpenGL rendering engine and tutorial scenes.
- `tutorial/src/main/assets`:
  - `shaders`: GLSL shader files for all tutorials.
  - `objects`: 3D models and geometry data.
  - `textures`: Image assets, including HDR cubemaps.
  - `fonts`: Font files for text rendering.

## 🔨 How to Build

1. Clone the repository.
2. Open the project in **Android Studio (Ladybug or newer recommended)**.
3. Ensure you have the **NDK** and **CMake** installed via the SDK Manager.
4. Sync the project with Gradle files.
5. Build and run the `tutorial` module on a device or emulator with GLES 3.0 support.

## 📜 License

This project is for educational purposes. Please refer to the licenses of included third-party libraries (Assimp, GLM, stb_image) for their respective terms.
