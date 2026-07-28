---
sidebar_position: 9
title: Compute Shader
---

# Compute Shader

Compute shaders enable general-purpose GPU computing (GPGPU), performing calculations outside the traditional rendering pipeline.

## 📋 Overview

In this tutorial, you will learn:

- What compute shaders are and how they work
- How to dispatch compute shader work groups
- How to share data between shaders using SSBOs
- Practical applications for compute shaders

## 🔑 Key Concepts

### Work Groups

Compute shaders execute in work groups:

- **Global Work Group**: Total number of work items
- **Local Work Group**: Subgroup of work items that share local memory
- **Work Item**: Individual execution of the shader

### Memory Types

| Memory Type | Access Speed | Scope |
|-------------|--------------|-------|
| Shared | Fastest | Local work group |
| Uniform | Fast | All work items |
| Storage (SSBO) | Medium | All work items |
| Image | Medium | All work items |

## 🧮 Mathematical Background

### Thread Coordinates

Each work item has unique coordinates:

- `gl_GlobalInvocationID`: Global position in the dispatch
- `gl_LocalInvocationID`: Position within the local work group
- `gl_WorkGroupID`: Position of the local work group

## 📝 Code Walkthrough

### Compute Shader Example

```glsl
#version 320 es
layout (local_size_x = 16, local_size_y = 16) in;

layout (binding = 0) uniform sampler2D inputTexture;
layout (binding = 1, rgba8) uniform writeonly image2D outputImage;

void main() {
    ivec2 texCoord = ivec2(gl_GlobalInvocationID.xy);
    vec4 color = texelFetch(inputTexture, texCoord, 0);
    
    color.rgb = 1.0 - color.rgb;
    imageStore(outputImage, texCoord, color);
}
```

### Dispatching Compute Shader

```cpp
GLuint computeShader; // Compiled compute shader program
glUseProgram(computeShader);

// Bind textures/buffers
glBindImageTexture(1, outputTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);

// Dispatch work groups
glDispatchCompute(width / 16, height / 16, 1);

// Wait for completion
glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
```

## 🎮 Interactive Demo

In the app, observe compute shader effects like image processing or particle simulations.

## ⚠️ Common Pitfalls

1. **Work group size**: Must be a multiple of local work group size
2. **Memory barriers**: Use `glMemoryBarrier` after compute shader dispatch
3. **Resource conflicts**: Ensure proper synchronization when multiple shaders access the same resources

## 🧪 Exercises

1. **Image processing**: Implement blur, sharpen, or edge detection
2. **Particle simulation**: Update particle positions on the GPU
3. **Physics computation**: Compute collision detection

## 📚 References

- [OpenGL ES 3.1 Compute Shaders](https://www.khronos.org/opengles/sdk/docs/man3/html/glDispatchCompute.xhtml)
- [LearnOpenGL - Compute Shader](https://learnopengl.com/Advanced-OpenGL/Compute-Shader)
