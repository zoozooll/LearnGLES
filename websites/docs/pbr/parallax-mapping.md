---
sidebar_position: 3
title: Parallax Mapping
---

# Parallax Mapping

Parallax mapping simulates depth in textures by offsetting texture coordinates.

## 📋 Overview

In this tutorial, you will learn:

- What parallax mapping is and why it's used
- How to implement parallax mapping
- Parallax occlusion mapping
- Steep parallax mapping

## 🔑 Key Concepts

### Parallax Mapping

Parallax mapping offsets texture coordinates based on:
- View direction
- Height map values
- Scale factor

### Height Map

A height map is a grayscale texture:
- White (1.0): High points
- Black (0.0): Low points

### Types of Parallax Mapping

- **Basic parallax**: Simple offset
- **Steep parallax**: Multiple samples for steep angles
- **Parallax occlusion**: Ray marching with self-occlusion

## 🧮 Mathematical Background

### Texture Coordinate Offset

```
offset = view_dir.xy * height * scale
new_tex_coord = tex_coord + offset
```

### Ray Marching (Parallax Occlusion)

For each step along the view ray:
1. Sample height at current position
2. Compare with ray depth
3. If height >= depth, the ray hits the surface

## 📝 Code Walkthrough

### Basic Parallax Mapping

```glsl
#version 320 es
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D heightMap;
uniform float heightScale;

void main() {
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    
    // Get height from height map
    float height = texture(heightMap, fs_in.TexCoords).r;
    
    // Calculate texture coordinate offset
    vec2 p = viewDir.xy / viewDir.z * height * heightScale;
    vec2 texCoords = fs_in.TexCoords + p;
    
    // Get normal from displaced coordinates
    vec3 normal = texture(normalMap, texCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    
    // ... lighting calculation
}
```

### Parallax Occlusion Mapping

```glsl
vec2 ParallaxOcclusionMapping(vec2 texCoords, vec3 viewDir) {
    const int layers = 32;
    float layerDepth = 1.0 / float(layers);
    float currentLayerDepth = 0.0;
    
    vec2 P = viewDir.xy * heightScale;
    vec2 deltaTexCoords = P / float(layers);
    
    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = texture(heightMap, currentTexCoords).r;
    
    while (currentLayerDepth < currentDepthMapValue) {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(heightMap, currentTexCoords).r;
        currentLayerDepth += layerDepth;
    }
    
    // Binary search for better precision
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;
    float prevDepthMapValue = texture(heightMap, prevTexCoords).r;
    
    float afterDepth = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = prevDepthMapValue - (currentLayerDepth - layerDepth);
    
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);
    
    return finalTexCoords;
}
```

## 🎮 Interactive Demo

In the app, see depth effects with parallax mapping.

## ⚠️ Common Pitfalls

1. **Scale factor**: Too high = distorted textures, too low = no effect
2. **Layer count**: More layers = better quality but slower
3. **Edge artifacts**: Texture coordinates may go outside 0-1 range
4. **Performance**: Parallax occlusion mapping is expensive

## 🧪 Exercises

1. **Layer count adjustment**: Allow users to adjust layer count
2. **Scale adjustment**: Allow users to adjust height scale
3. **Relief mapping**: Implement relief mapping for better quality

## 📚 References

- [LearnOpenGL - Parallax Mapping](https://learnopengl.com/Advanced-Lighting/Parallax-Mapping)
