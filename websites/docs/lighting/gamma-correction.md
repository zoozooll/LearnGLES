---
sidebar_position: 5
title: Gamma Correction
---

# Gamma Correction

Gamma correction ensures colors are displayed correctly on different devices.

## 📋 Overview

In this tutorial, you will learn:

- What gamma is and why it matters
- How to implement gamma correction
- Linear vs gamma space rendering
- Texture gamma correction

## 🔑 Key Concepts

### Gamma

Gamma is the non-linear relationship between pixel values and perceived brightness:

- **CRT monitors**: Gamma ~2.2
- **Modern displays**: Gamma ~2.2-2.4
- **Human eye**: Responds logarithmically to light intensity

### Linear vs Gamma Space

- **Linear space**: Colors are mathematically correct
- **Gamma space**: Colors appear correct on displays

### Gamma Correction Pipeline

1. **Decode**: Convert from gamma space to linear space
2. **Process**: Perform lighting calculations in linear space
3. **Encode**: Convert back to gamma space for display

## 🧮 Mathematical Background

### Gamma Correction Formulas

**Gamma encoding (display):**
```
display_value = linear_value^(1/gamma)
```

**Gamma decoding (texture):**
```
linear_value = texture_value^gamma
```

**Typical gamma values:**
- sRGB: gamma = 2.4 (approx)
- Most textures: gamma = 2.2

## 📝 Code Walkthrough

### Enabling Gamma Correction

```cpp
glEnable(GL_FRAMEBUFFER_SRGB);
```

### Manual Gamma Correction in Shader

```glsl
// Decode gamma from textures
vec3 albedo = pow(texture(material.albedo, TexCoords).rgb, 2.2);

// Perform lighting calculations in linear space
vec3 result = lightingCalculation(albedo, ...);

// Encode gamma for display
FragColor = vec4(pow(result, vec3(1.0/2.2)), 1.0);
```

### Texture Format

```cpp
// Load texture with sRGB format
glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, 
             GL_RGBA, GL_UNSIGNED_BYTE, data);
```

## 🎮 Interactive Demo

In the app, see the difference between gamma-corrected and non-gamma-corrected rendering.

## ⚠️ Common Pitfalls

1. **Double correction**: Don't apply gamma correction twice
2. **Normal maps**: Keep normal maps in linear space
3. **HDR textures**: HDR textures are already linear
4. **Framebuffer SRGB**: Only works if the framebuffer supports sRGB

## 🧪 Exercises

1. **Gamma visualization**: Create a tool to visualize gamma curves
2. **Custom gamma**: Allow users to adjust gamma settings
3. **Color grading**: Apply color grading in linear space

## 📚 References

- [LearnOpenGL - Gamma Correction](https://learnopengl.com/Advanced-Lighting/Gamma-Correction)
