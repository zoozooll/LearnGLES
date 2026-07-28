---
sidebar_position: 3
title: OIT (Order Independent Transparency)
---

# OIT (Order Independent Transparency)

OIT renders transparent objects correctly regardless of draw order.

## 📋 Overview

In this tutorial, you will learn:

- What OIT is and why it's needed
- Different OIT techniques
- How to implement OIT
- Performance considerations

## 🔑 Key Concepts

### Traditional Transparency

Traditional transparency requires objects to be sorted back to front:
- Expensive for dynamic scenes
- Fragments with multiple transparent layers need careful handling

### OIT Techniques

- **Weighted Blended OIT**: Simple, good for many layers
- **Depth Peeling**: More accurate, but limited to few layers
- **Linked Lists**: Hardware-accelerated, but requires specific GPU support

### Weighted Blended OIT

Stores multiple transparent layers in a single pass:
- Accumulate color with weight
- Accumulate weight
- Final color = accumulated color / accumulated weight

## 🧮 Mathematical Background

### Weight Calculation

```
weight = max(1e-4, min(3e3, 10.0 / (1e-5 + pow(2 * depth, 4.0))))
```

### Accumulation

```
accumulated_color += color * alpha * weight
accumulated_weight += alpha * weight
final_color = accumulated_color / accumulated_weight
```

## 📝 Code Walkthrough

### OIT Framebuffer Setup

```cpp
// Create accumulation texture (RGBA16F)
glGenTextures(1, &accumulationTexture);
glBindTexture(GL_TEXTURE_2D, accumulationTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

// Create revealage texture (R16F)
glGenTextures(1, &revealageTexture);
glBindTexture(GL_TEXTURE_2D, revealageTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, width, height, 0, GL_RED, GL_FLOAT, nullptr);

// Attach to framebuffer
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, accumulationTexture, 0);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, revealageTexture, 0);
```

### OIT Fragment Shader

```glsl
#version 320 es
layout (location = 0) out vec4 FragColor;
layout (location = 1) out float FragRevealage;

in VS_OUT {
    vec2 TexCoords;
    vec3 FragPos;
} fs_in;

uniform sampler2D albedoMap;
uniform float alpha;

void main() {
    vec3 color = texture(albedoMap, fs_in.TexCoords).rgb;
    
    float depth = gl_FragCoord.z / gl_FragCoord.w;
    
    float weight = clamp(pow(min(1.0, alpha * 10.0) + 0.01, 3.0) * 1000.0 * pow(1.0 - depth * 0.9, 3.0), 1e-2, 3e3);
    
    FragColor = vec4(color * alpha * weight, alpha);
    FragRevealage = alpha;
}
```

### OIT Blend Shader

```glsl
#version 320 es
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D accumulationTexture;
uniform sampler2D revealageTexture;
uniform sampler2D opaqueTexture;

void main() {
    vec4 accum = texture(accumulationTexture, TexCoords);
    float revealage = texture(revealageTexture, TexCoords).r;
    
    vec3 color = accum.rgb / max(accum.a, 1e-4);
    vec3 opaque = texture(opaqueTexture, TexCoords).rgb;
    
    FragColor = vec4(mix(opaque, color, revealage), 1.0);
}
```

## 🎮 Interactive Demo

In the app, see correct transparency with OIT.

## ⚠️ Common Pitfalls

1. **Texture format**: Must use floating-point textures
2. **Weight function**: Incorrect weight function causes artifacts
3. **Performance**: OIT is more expensive than traditional transparency
4. **Memory**: Accumulation textures use more memory

## 🧪 Exercises

1. **OIT quality**: Compare different weight functions
2. **Depth peeling**: Implement depth peeling for better quality
3. **Hybrid approach**: Use OIT for complex scenes, traditional for simple ones

## 📚 References

- [Weighted Blended OIT](http://jcgt.org/published/0002/02/09/)
