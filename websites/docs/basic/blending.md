---
sidebar_position: 5
title: Blending
---

# Blending

Blending combines the color of a new pixel with the color already in the framebuffer, enabling transparency effects.

## 📋 Overview

In this tutorial, you will learn:

- How blending works in OpenGL ES
- Different blend modes
- How to render transparent objects correctly
- Alpha testing vs alpha blending

## 🔑 Key Concepts

### Blending Equation

The blending equation combines source and destination colors:

```
final_color = source_color * source_factor + destination_color * destination_factor
```

### Common Blend Modes

| Mode | Source Factor | Destination Factor | Description |
|------|---------------|--------------------|-------------|
| Normal | `GL_SRC_ALPHA` | `GL_ONE_MINUS_SRC_ALPHA` | Standard transparency |
| Additive | `GL_ONE` | `GL_ONE` | Glowing effects |
| Multiplicative | `GL_DST_COLOR` | `GL_ZERO` | Darkening effect |

## 🧮 Mathematical Background

### Alpha Values

Alpha values range from 0.0 (fully transparent) to 1.0 (fully opaque). For correct transparency:

1. Sort objects by distance from camera (back to front)
2. Disable depth writing for transparent objects
3. Enable blending

## 📝 Code Walkthrough

### Enabling Blending

```cpp
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
```

### Rendering Transparent Objects

```cpp
glDepthMask(GL_FALSE); // Disable depth writing
// Draw transparent objects (sorted back to front)
glDepthMask(GL_TRUE); // Re-enable depth writing
```

## 🎮 Interactive Demo

In the app, observe transparent objects like glass or particles.

## ⚠️ Common Pitfalls

1. **Not sorting transparent objects**: Objects may render incorrectly
2. **Depth writing enabled**: Transparent objects will occlude other objects
3. **Blending disabled**: Objects won't be transparent

## 🧪 Exercises

1. **Additive blending**: Create a glowing effect
2. **Multi-layer transparency**: Stack multiple transparent objects
3. **Alpha testing**: Use `glAlphaFunc` for hard edges

## 📚 References

- [OpenGL ES 3.0 Blending](https://www.khronos.org/opengles/sdk/docs/man3/html/glBlendFunc.xhtml)
- [LearnOpenGL - Blending](https://learnopengl.com/Advanced-OpenGL/Blending)
