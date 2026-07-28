---
sidebar_position: 4
title: Stencil Testing
---

# Stencil Testing

Stencil testing uses a stencil buffer to control which pixels are drawn, enabling complex visual effects.

## 📋 Overview

In this tutorial, you will learn:

- What the stencil buffer is and how it works
- How to use stencil testing for effects like outlines
- Different stencil operations

## 🔑 Key Concepts

### Stencil Buffer

The stencil buffer is a 2D array that stores an integer value for each pixel. It's used to:

1. **Mark** regions of the screen
2. **Mask** out regions where drawing should be prevented
3. **Count** how many times a pixel has been drawn

### Stencil Operations

When a stencil test passes or fails, you can specify what happens to the stencil buffer value:

| Operation | Description |
|-----------|-------------|
| `GL_KEEP` | Keep the current value |
| `GL_ZERO` | Set to 0 |
| `GL_REPLACE` | Replace with the reference value |
| `GL_INCR` | Increment (clamped to max) |
| `GL_DECR` | Decrement (clamped to 0) |
| `GL_INVERT` | Bitwise invert |

## 🧮 Mathematical Background

### Stencil Test Logic

```
reference & mask comparisonFunction (stencil_buffer & mask)
```

Where:
- `reference`: The reference value set by `glStencilFunc`
- `mask`: A bitmask applied to both reference and buffer values
- `comparisonFunction`: One of `GL_NEVER`, `GL_LESS`, `GL_EQUAL`, etc.

## 📝 Code Walkthrough

### Setting Up Stencil Testing

```cpp
glEnable(GL_STENCIL_TEST);
glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Test: not equal to 1
glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // Pass: replace with ref
```

### Creating an Outline Effect

1. **First pass**: Draw the object, writing 1 to stencil buffer where object is drawn
2. **Second pass**: Disable stencil writing, draw the object slightly larger where stencil != 1

## 🎮 Interactive Demo

In the app, observe the outline effect on 3D objects.

## ⚠️ Common Pitfalls

1. **Forgetting to enable stencil test**: `glEnable(GL_STENCIL_TEST)`
2. **Incorrect framebuffer configuration**: Ensure stencil buffer is allocated
3. **Not clearing the stencil buffer**: Previous values will interfere

## 🧪 Exercises

1. **Create a mirror effect**: Use stencil to draw a reflection
2. **Layered rendering**: Use stencil values to control multiple layers
3. **Custom stencil operations**: Experiment with different increment/decrement patterns

## 📚 References

- [OpenGL ES 3.0 Stencil Test](https://www.khronos.org/opengles/sdk/docs/man3/html/glStencilFunc.xhtml)
- [LearnOpenGL - Stencil Testing](https://learnopengl.com/Advanced-OpenGL/Stencil-testing)
