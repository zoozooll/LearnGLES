---
sidebar_position: 7
title: Geometry Shader
---

# Geometry Shader

Geometry shaders process entire primitives (points, lines, triangles) and can generate new geometry.

## 📋 Overview

In this tutorial, you will learn:

- What geometry shaders are and how they work
- How to generate new geometry on the GPU
- Practical uses for geometry shaders

## 🔑 Key Concepts

### Geometry Shader Pipeline

Geometry shaders sit between the vertex and fragment shaders:

1. **Input**: A primitive (point, line, triangle, or adjacency primitive)
2. **Processing**: The shader can examine all vertices of the primitive
3. **Output**: Zero or more new primitives

### Built-in Variables

- `gl_in[]`: Array of input vertices
- `gl_PrimitiveIDIn`: Primitive ID
- `gl_InvocationID`: For instanced geometry shaders

## 🧮 Mathematical Background

### Primitive Generation

Geometry shaders can generate new vertices using `EmitVertex()` and `EndPrimitive()`. This is useful for:

- **Point sprites**: Expand points into quads
- **Wireframe**: Generate lines from triangles
- **Explosion effects**: Displace vertices

## 📝 Code Walkthrough

### Geometry Shader Example

```glsl
#version 320 es
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main() {
    for(int i = 0; i < gl_in.length(); i++) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
```

### Creating Point Sprites

Geometry shaders can expand a single point into a quad facing the camera:

```glsl
#version 320 es
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 projection;

void main() {
    vec4 pos = gl_in[0].gl_Position;
    // Generate quad corners
    gl_Position = projection * (pos + vec4(-0.1, -0.1, 0, 0));
    EmitVertex();
    gl_Position = projection * (pos + vec4(0.1, -0.1, 0, 0));
    EmitVertex();
    gl_Position = projection * (pos + vec4(-0.1, 0.1, 0, 0));
    EmitVertex();
    gl_Position = projection * (pos + vec4(0.1, 0.1, 0, 0));
    EmitVertex();
    EndPrimitive();
}
```

## 🎮 Interactive Demo

In the app, observe geometry shader effects like point sprites or wireframe rendering.

## ⚠️ Common Pitfalls

1. **Performance**: Geometry shaders can be slow if generating too many vertices
2. **Max vertices**: Don't exceed `max_vertices` limit
3. **Primitive type mismatch**: Ensure input/output primitive types match

## 🧪 Exercises

1. **Wireframe overlay**: Generate wireframe lines on top of solid geometry
2. **Explosion effect**: Push vertices away from center
3. **Grass rendering**: Generate grass blades from point data

## 📚 References

- [OpenGL ES 3.0 Geometry Shaders](https://www.khronos.org/opengles/sdk/docs/man3/html/glCreateShader.xhtml)
- [LearnOpenGL - Geometry Shader](https://learnopengl.com/Advanced-OpenGL/Geometry-Shader)
