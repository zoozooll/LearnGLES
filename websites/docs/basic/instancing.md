---
sidebar_position: 10
title: Instancing
---

# Instancing

Instancing efficiently renders many copies of the same object with a single draw call.

## 📋 Overview

In this tutorial, you will learn:

- What instancing is and why it's important
- How to use instanced rendering
- How to pass per-instance data
- Practical uses for instancing

## 🔑 Key Concepts

### Instanced Rendering

Instancing allows rendering multiple copies of the same mesh with:

- **Shared data**: Positions, normals, texture coordinates (same for all instances)
- **Per-instance data**: Model matrices, colors, offsets (different for each instance)

### Instanced Vertex Attributes

Use `glVertexAttribDivisor` to specify how often an attribute updates:

- `0`: Update per vertex (default)
- `1`: Update per instance

## 🧮 Mathematical Background

### Performance Benefits

Without instancing:
- N objects = N draw calls
- N shader program bindings
- N matrix uploads

With instancing:
- N objects = 1 draw call
- 1 shader program binding
- 1 buffer upload for all instance data

## 📝 Code Walkthrough

### Setting Up Instanced Attributes

```cpp
// Create instance data buffer
glGenBuffers(1, &instanceVBO);
glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(modelMatrices), &modelMatrices[0], GL_STATIC_DRAW);

// Set up instanced attributes
for (unsigned int i = 0; i < 4; i++) {
    glEnableVertexAttribArray(3 + i);
    glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), 
                          (void*)(sizeof(glm::vec4) * i));
    glVertexAttribDivisor(3 + i, 1); // Update per instance
}
```

### Drawing with Instancing

```cpp
glBindVertexArray(VAO);
glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100); // 100 instances
```

## 🎮 Interactive Demo

In the app, observe how hundreds of objects are rendered efficiently.

## ⚠️ Common Pitfalls

1. **Instanced attribute divisor**: Forgetting `glVertexAttribDivisor` will cause all instances to use the same data
2. **Buffer size**: Ensure instance buffer is large enough
3. **Performance**: Instancing has overhead; use for 10+ instances

## 🧪 Exercises

1. **Per-instance colors**: Give each instance a unique color
2. **Instanced animation**: Animate each instance differently
3. **Dynamic instancing**: Update instance data every frame

## 📚 References

- [OpenGL ES 3.0 Instanced Rendering](https://www.khronos.org/opengles/sdk/docs/man3/html/glDrawArraysInstanced.xhtml)
- [LearnOpenGL - Instancing](https://learnopengl.com/Advanced-OpenGL/Instancing)
