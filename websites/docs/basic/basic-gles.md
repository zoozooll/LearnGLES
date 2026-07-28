---
sidebar_position: 2
title: Basic GLES
---

# Basic GLES

Welcome to the first tutorial! This tutorial introduces the fundamental concepts of OpenGL ES rendering, including shaders, textures, and transformations.

## 📋 Overview

In this tutorial, you will learn:

- How to set up an OpenGL ES context on Android
- How to write vertex and fragment shaders
- How to load and apply textures
- How to use model-view-projection matrices

## 🔑 Key Concepts

### Shaders

Shaders are programs that run on the GPU. There are two main types:

- **Vertex Shader**: Processes each vertex, transforming its position from model space to screen space
- **Fragment Shader**: Processes each pixel, determining its final color

### Textures

Textures are 2D images applied to 3D surfaces to add detail. They are sampled in the fragment shader.

### Transformations

Three types of transformations are applied to every vertex:

1. **Model Matrix**: Positions the object in world space
2. **View Matrix**: Represents the camera's position and orientation
3. **Projection Matrix**: Projects 3D points onto the 2D screen

## 🧮 Mathematical Background

### Model-View-Projection (MVP) Matrix

The MVP matrix is the product of three matrices:

```
MVP = Projection × View × Model
```

This transforms a vertex from local model space to screen space:

1. **Model**: `v_world = Model × v_local`
2. **View**: `v_view = View × v_world`
3. **Projection**: `v_clip = Projection × v_view`

### Perspective Projection

The perspective projection matrix creates the illusion of depth:

```
P = [
    f/aspect  0   0   0
    0         f   0   0
    0         0   (n+f)/(n-f)   2nf/(n-f)
    0         0   -1   0
]

where f = cot(fovy/2), n = near plane, f = far plane
```

## 📝 Code Walkthrough

### Scene Initialization

In [BasicGlesScene.cpp](file:///e:/workspaces/cpp/LearnGLES/tutorial/src/main/cpp/basic/BasicGlesScene.cpp), the `init()` method:

1. Enables depth testing: `glEnable(GL_DEPTH_TEST)`
2. Creates a camera: `camera = new TargetCamera()`
3. Loads shaders: `m_pShader = new Shader("shaders/basic_gles/basic.vert", "shaders/basic_gles/basic.frag")`
4. Creates vertex buffers: `glGenVertexArrays()`, `glGenBuffers()`
5. Loads textures: `loadTexture("textures/container.jpg")`

### Drawing

In the `draw()` method:

1. Updates the camera: `camera->update()`
2. Clears the framebuffer: `glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)`
3. Binds textures to texture units
4. Sets uniform matrices (projection, view, model)
5. Draws the geometry: `glDrawArrays(GL_TRIANGLES, 0, 36)`

## 🎮 Interactive Demo

In the app, you can interact with this tutorial using:

- **Single finger drag**: Rotate the camera around the cubes
- **Two finger pinch**: Zoom in/out
- **Double tap**: Reset the camera position

## ⚠️ Common Pitfalls

1. **Forgetting to enable depth testing**: Objects will render in the order they are drawn, not by depth
2. **Incorrect matrix multiplication order**: Remember `MVP = P × V × M`, not `M × V × P`
3. **Not setting texture uniforms**: Textures won't be applied if the sampler isn't bound to the correct texture unit
4. **Vertex attribute misalignment**: Ensure the stride and offset parameters in `glVertexAttribPointer` match your vertex layout

## 🧪 Exercises

1. **Modify the cube colors**: Change the base color in the fragment shader
2. **Add rotation**: Make one cube rotate over time
3. **Change the number of cubes**: Add or remove cubes from the scene
4. **Change texture wrapping**: Experiment with `GL_REPEAT`, `GL_CLAMP_TO_EDGE`, `GL_MIRRORED_REPEAT`

## 📚 References

- [OpenGL ES 3.0 Specification](https://www.khronos.org/registry/OpenGL/specs/es/3.0/es_spec_3.0.pdf)
- [LearnOpenGL - Getting Started](https://learnopengl.com/Getting-started/Hello-Triangle)
- [GLM Documentation](https://glm.g-truc.net/0.9.9/api/index.html)
