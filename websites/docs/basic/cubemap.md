---
sidebar_position: 6
title: Cubemap
---

# Cubemap

Cubemaps are 6-texture arrays used for skyboxes and environment mapping.

## 📋 Overview

In this tutorial, you will learn:

- What cubemaps are and how they work
- How to create skyboxes
- How to implement environment mapping
- Reflection and refraction effects

## 🔑 Key Concepts

### Cubemap Layout

A cubemap consists of 6 textures arranged in a cross pattern:

- Positive X (right)
- Negative X (left)
- Positive Y (top)
- Negative Y (bottom)
- Positive Z (front)
- Negative Z (back)

### Skyboxes

Skyboxes use a cubemap to create the illusion of a surrounding environment. The camera is placed at the center of the cube.

### Environment Mapping

Environment mapping uses the cubemap to simulate reflections on shiny surfaces. The reflection direction is calculated using the normal and view vectors.

## 🧮 Mathematical Background

### Reflection Vector

The reflection direction is calculated using the formula:

```
R = I - 2 * (I · N) * N
```

Where:
- `R`: Reflection direction
- `I`: Incoming direction (view vector)
- `N`: Surface normal

## 📝 Code Walkthrough

### Loading a Cubemap

```cpp
std::vector<std::string> faces = {
    "textures/skybox/right.jpg",
    "textures/skybox/left.jpg",
    "textures/skybox/top.jpg",
    "textures/skybox/bottom.jpg",
    "textures/skybox/front.jpg",
    "textures/skybox/back.jpg"
};
unsigned int cubemapTexture = loadCubemap(faces);
```

### Skybox Shader

The skybox vertex shader passes through positions without applying perspective:

```glsl
void main() {
    vec4 pos = projection * view * vec4(position, 1.0);
    gl_Position = pos.xyww; // Keep depth at maximum
}
```

## 🎮 Interactive Demo

In the app, observe the skybox surrounding the scene and reflective objects.

## ⚠️ Common Pitfalls

1. **Cubemap texture order**: Ensure textures are loaded in the correct order
2. **Skybox rendering order**: Render skybox first (before other objects)
3. **Depth testing**: Disable depth writing for skybox

## 🧪 Exercises

1. **Refraction**: Implement refraction with different refractive indices
2. **Dynamic cubemap**: Render the scene into a cubemap at runtime
3. **Irradiance map**: Create a precomputed irradiance cubemap

## 📚 References

- [OpenGL ES 3.0 Cubemaps](https://www.khronos.org/opengles/sdk/docs/man3/html/glTexImage2D.xhtml)
- [LearnOpenGL - Cubemaps](https://learnopengl.com/Advanced-OpenGL/Cubemaps)
