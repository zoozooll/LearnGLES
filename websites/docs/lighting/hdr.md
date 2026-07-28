---
sidebar_position: 8
title: HDR
---

# HDR (High Dynamic Range)

HDR rendering allows for brighter highlights and darker shadows, creating more realistic images.

## 📋 Overview

In this tutorial, you will learn:

- What HDR is and why it matters
- How to implement HDR rendering
- Tone mapping techniques
- How to combine HDR with bloom

## 🔑 Key Concepts

### Dynamic Range

- **LDR (Low Dynamic Range)**: 0.0-1.0 range, limited contrast
- **HDR (High Dynamic Range)**: Extended range beyond 1.0, realistic contrast

### HDR Pipeline

1. **Render to HDR framebuffer**: Store colors beyond 1.0
2. **Apply tone mapping**: Convert HDR to LDR for display
3. **Apply gamma correction**: Ensure correct display

### Tone Mapping

Tone mapping compresses HDR values to LDR:
- Reinhard tone mapping
- ACES tone mapping
- Exposure-based tone mapping

## 🧮 Mathematical Background

### Reinhard Tone Mapping

```
result = color / (1 + color)
```

Simple but doesn't preserve highlights well.

### Exposure-Based Tone Mapping

```
result = 1 - exp(-color * exposure)
```

Controls brightness via exposure parameter.

### ACES Tone Mapping (Approximation)

```
color *= 0.6;
float a = 2.51;
float b = 0.03;
float c = 2.43;
float d = 0.59;
float e = 0.14;
result = clamp((color * (a * color + b)) / (color * (c * color + d) + e), 0.0, 1.0);
```

More cinematic, used in film and games.

## 📝 Code Walkthrough

### Creating HDR Framebuffer

```cpp
glGenFramebuffers(1, &hdrFBO);
glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

// Create HDR texture
glGenTextures(1, &hdrTexture);
glBindTexture(GL_TEXTURE_2D, hdrTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// Attach texture to framebuffer
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, hdrTexture, 0);

// Create depth buffer
glGenRenderbuffers(1, &rbo);
glBindRenderbuffer(GL_RENDERBUFFER, rbo);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
```

### Tone Mapping Shader

```glsl
#version 320 es
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrTexture;
uniform float exposure;

void main() {
    vec3 hdrColor = texture(hdrTexture, TexCoords).rgb;
    
    // Exposure tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    
    // Gamma correction
    mapped = pow(mapped, vec3(1.0/2.2));
    
    FragColor = vec4(mapped, 1.0);
}
```

## 🎮 Interactive Demo

In the app, see HDR rendering with adjustable exposure.

## ⚠️ Common Pitfalls

1. **Floating-point texture**: Must use `GL_RGB16F` or `GL_RGB32F` format
2. **Exposure value**: Too high = washed out, too low = too dark
3. **Tone mapping order**: Apply tone mapping before gamma correction
4. **Bloom integration**: Extract bright pixels before tone mapping

## 🧪 Exercises

1. **Auto exposure**: Implement automatic exposure adjustment
2. **Manual exposure**: Allow users to adjust exposure in real-time
3. **Different tone mappers**: Compare Reinhard, ACES, and exposure-based

## 📚 References

- [LearnOpenGL - HDR](https://learnopengl.com/Advanced-Lighting/HDR)
