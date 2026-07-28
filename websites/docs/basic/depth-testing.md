---
sidebar_position: 3
title: Depth Testing
---

# Depth Testing

Depth testing ensures that objects closer to the camera are rendered on top of objects farther away.

## 📋 Overview

In this tutorial, you will learn:

- What depth testing is and why it's important
- How the depth buffer works
- Different depth functions
- When to enable/disable depth testing

## 🔑 Key Concepts

### Depth Buffer

The depth buffer (or z-buffer) is a 2D array that stores the depth (distance from camera) of each pixel. When a new pixel is rendered:

1. The pixel's depth is compared with the depth buffer value
2. If the test passes, the pixel is drawn and the depth buffer is updated
3. If the test fails, the pixel is discarded

### Depth Functions

OpenGL provides several depth comparison functions:

| Function | Description |
|----------|-------------|
| `GL_NEVER` | Never passes |
| `GL_LESS` | Passes if new depth < stored depth (default) |
| `GL_EQUAL` | Passes if new depth = stored depth |
| `GL_LEQUAL` | Passes if new depth `<=` stored depth |
| `GL_GREATER` | Passes if new depth > stored depth |
| `GL_NOTEQUAL` | Passes if new depth `!=` stored depth |
| `GL_GEQUAL` | Passes if new depth `>=` stored depth |
| `GL_ALWAYS` | Always passes |

## 🧮 Mathematical Background

### Depth Values

Depth values range from 0.0 (near plane) to 1.0 (far plane). However, the depth buffer uses a **non-linear** distribution:

```
z_ndc = (2.0 * z - near - far) / (far - near)
depth = (z_ndc + 1.0) / 2.0
```

This means more precision is allocated to objects near the camera.

## 📝 Code Walkthrough

### Enabling Depth Testing

```cpp
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS); // Set depth comparison function
```

### Clearing the Depth Buffer

```cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

### Disabling Depth Testing

```cpp
glDisable(GL_DEPTH_TEST);
```

## 🎮 Interactive Demo

In the app, observe how cubes are correctly ordered by depth.

## ⚠️ Common Pitfalls

1. **Forgetting to clear the depth buffer**: Previous frame's depth values will interfere
2. **Depth precision issues**: Objects far away may have incorrect depth ordering
3. **Not enabling depth testing**: Objects render in draw order, not depth order

## 🧪 Exercises

1. **Change depth function**: Try `GL_GREATER` to see inverted depth
2. **Depth clamping**: Use `glEnable(GL_DEPTH_CLAMP)` to clamp depth values
3. **Depth mask**: Use `glDepthMask(GL_FALSE)` to prevent writing to depth buffer

## 📚 References

- [OpenGL ES 3.0 Depth Test](https://www.khronos.org/opengles/sdk/docs/man3/html/glDepthFunc.xhtml)
- [LearnOpenGL - Depth Testing](https://learnopengl.com/Advanced-OpenGL/Depth-testing)
