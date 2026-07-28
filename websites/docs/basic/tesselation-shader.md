---
sidebar_position: 8
title: Tessellation Shader
---

# Tessellation Shader

Tessellation shaders dynamically subdivide geometry on the GPU, enabling level-of-detail rendering.

## 📋 Overview

In this tutorial, you will learn:

- What tessellation shaders are and how they work
- The two stages: tessellation control and evaluation
- How to control subdivision levels
- Practical uses for tessellation

## 🔑 Key Concepts

### Tessellation Pipeline

Tessellation has two shader stages:

1. **Tessellation Control Shader (TCS)**: Runs once per input vertex, determines subdivision level
2. **Tessellation Evaluation Shader (TES)**: Runs once per generated vertex, positions new vertices

### Patch Primitive

Tessellation works on "patches" - groups of vertices. Common patch types:

- Triangles (3 vertices)
- Quadrilaterals (4 vertices)
- Isolines (2 vertices)

## 🧮 Mathematical Background

### Subdivision Levels

The TCS specifies how many times to subdivide:

- `gl_TessLevelInner`: Inner subdivision factors
- `gl_TessLevelOuter`: Outer subdivision factors

### Barycentric Coordinates

The TES receives barycentric coordinates that indicate the position within the primitive:

- Triangle: (u, v, w) where u + v + w = 1
- Quad: (u, v) where 0 ≤ u, v ≤ 1

## 📝 Code Walkthrough

### Tessellation Control Shader

```glsl
#version 320 es
layout (vertices = 3) out;

void main() {
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    
    if (gl_InvocationID == 0) {
        gl_TessLevelInner[0] = 4.0;
        gl_TessLevelOuter[0] = 4.0;
        gl_TessLevelOuter[1] = 4.0;
        gl_TessLevelOuter[2] = 4.0;
    }
}
```

### Tessellation Evaluation Shader

```glsl
#version 320 es
layout (triangles, equal_spacing, cw) in;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    vec4 pos = gl_TessCoord.x * gl_in[0].gl_Position +
               gl_TessCoord.y * gl_in[1].gl_Position +
               gl_TessCoord.z * gl_in[2].gl_Position;
    gl_Position = projection * view * model * pos;
}
```

## 🎮 Interactive Demo

In the app, observe how geometry is dynamically subdivided based on distance.

## ⚠️ Common Pitfalls

1. **Patch vertex count**: Ensure `layout (vertices = N)` matches your patch size
2. **Performance**: High subdivision levels can be expensive
3. **Edge cracking**: Ensure adjacent patches have matching subdivision levels

## 🧪 Exercises

1. **Adaptive tessellation**: Adjust subdivision based on distance from camera
2. **Displacement mapping**: Use height maps to displace vertices
3. **Curved surfaces**: Create smooth curved surfaces from low-poly meshes

## 📚 References

- [OpenGL ES 3.0 Tessellation Shaders](https://www.khronos.org/opengles/sdk/docs/man3/html/glCreateShader.xhtml)
- [LearnOpenGL - Tessellation Shader](https://learnopengl.com/Advanced-OpenGL/Tessellation)
