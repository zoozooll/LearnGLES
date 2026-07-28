---
sidebar_position: 9
title: Bloom
---

# Bloom

Bloom adds a glow effect around bright objects, simulating light scattering in the eye.

## 📋 Overview

In this tutorial, you will learn:

- What bloom is and why it's used
- How to implement bloom
- Gaussian blur techniques
- Different bloom quality levels

## 🔑 Key Concepts

### Bloom Pipeline

1. **Extract bright pixels**: Render bright areas to a separate texture
2. **Blur**: Apply Gaussian blur to bright pixels
3. **Combine**: Add blurred bright pixels to the original image

### Gaussian Blur

Gaussian blur uses a weighted kernel:
- Separable blur (horizontal + vertical)
- Kernel size affects blur quality
- Sigma controls blur spread

### Bloom Quality

- **Low quality**: Single blur pass
- **Medium quality**: Multiple blur passes
- **High quality**: Multiple passes with increasing kernel size

## 🧮 Mathematical Background

### Gaussian Function

```
G(x, y) = exp(-(x^2 + y^2) / (2 * sigma^2)) / (2 * PI * sigma^2)
```

### Separable Blur

A 2D Gaussian blur can be separated into two 1D passes:
1. Horizontal pass
2. Vertical pass

This reduces complexity from O(n^2) to O(n).

## 📝 Code Walkthrough

### Bright Pass

```glsl
#version 320 es
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrTexture;
uniform float threshold;

void main() {
    vec3 color = texture(hdrTexture, TexCoords).rgb;
    float brightness = dot(color, vec3(0.2126, 0.7152, 0.0722));
    
    if (brightness > threshold) {
        FragColor = vec4(color, 1.0);
    } else {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
```

### Gaussian Blur Shader

```glsl
#version 320 es
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D image;
uniform bool horizontal;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {
    vec2 tex_offset = 1.0 / textureSize(image, 0);
    vec3 result = texture(image, TexCoords).rgb * weight[0];
    
    if (horizontal) {
        for (int i = 1; i < 5; ++i) {
            result += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    } else {
        for (int i = 1; i < 5; ++i) {
            result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    
    FragColor = vec4(result, 1.0);
}
```

### Combining Bloom

```glsl
#version 320 es
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrTexture;
uniform sampler2D bloomTexture;
uniform float bloomStrength;

void main() {
    vec3 hdrColor = texture(hdrTexture, TexCoords).rgb;
    vec3 bloomColor = texture(bloomTexture, TexCoords).rgb;
    
    vec3 result = hdrColor + bloomColor * bloomStrength;
    
    // Tone mapping and gamma correction
    result = 1.0 - exp(-result * exposure);
    result = pow(result, vec3(1.0/2.2));
    
    FragColor = vec4(result, 1.0);
}
```

## 🎮 Interactive Demo

In the app, see bloom effect on bright lights.

## ⚠️ Common Pitfalls

1. **Performance**: Multiple blur passes are expensive
2. **Texture format**: Use floating-point textures for HDR bloom
3. **Threshold**: Too low = too much bloom, too high = no bloom
4. **Artifacts**: Box blur can cause square artifacts; use Gaussian

## 🧪 Exercises

1. **Quality settings**: Allow users to adjust bloom quality
2. **Color grading**: Apply color grading to bloom
3. **Bloom only mode**: Show only the bloom effect

## 📚 References

- [LearnOpenGL - Bloom](https://learnopengl.com/Advanced-Lighting/Bloom)
