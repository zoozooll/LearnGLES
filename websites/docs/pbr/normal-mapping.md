---
sidebar_position: 2
title: Normal Mapping
---

# Normal Mapping

Normal mapping adds surface detail without increasing polygon count.

## 📋 Overview

In this tutorial, you will learn:

- What normal mapping is and why it's used
- How to implement normal mapping
- Tangent space vs object space
- How to create normal maps

## 🔑 Key Concepts

### Normal Maps

A normal map is a texture that stores surface normals:
- RGB channels represent XYZ components
- Normals are encoded as 0-1 (instead of -1 to 1)
- Applied per-fragment, creating detailed surfaces

### Tangent Space

Tangent space normals are relative to the surface:
- Tangent: Parallel to surface, along texture U axis
- Bitangent: Parallel to surface, along texture V axis
- Normal: Perpendicular to surface

### TBN Matrix

The TBN matrix transforms normals from tangent space to world space:

```
world_normal = TBN * tangent_space_normal
```

## 🧮 Mathematical Background

### Normal Encoding

Normals are encoded in RGB:

```
encoded_normal = (normal + 1.0) / 2.0
```

Decoding:

```
normal = encoded_normal * 2.0 - 1.0
```

### Tangent Calculation

Tangents are calculated from texture coordinates:

```
tangent = (deltaPos1 * uv2.y - deltaPos2 * uv1.y) / (uv1.x * uv2.y - uv2.x * uv1.y)
bitangent = cross(normal, tangent)
```

## 📝 Code Walkthrough

### Vertex Shader with Tangents

```glsl
#version 320 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out VS_OUT {
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
    vs_out.TexCoords = aTexCoords;
    
    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));
    
    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos = TBN * viewPos;
    vs_out.TangentFragPos = TBN * vec3(model * vec4(aPos, 1.0));
}
```

### Fragment Shader with Normal Mapping

```glsl
#version 320 es
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D normalMap;

void main() {
    // Get normal from normal map in range [-1, 1]
    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    
    // Calculate lighting using tangent space normals
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    
    vec3 result = (diff + spec) * lightColor;
    FragColor = vec4(result, 1.0);
}
```

## 🎮 Interactive Demo

In the app, see detailed surfaces with normal mapping.

## ⚠️ Common Pitfalls

1. **Normal decoding**: Don't forget to decode from 0-1 to -1-1
2. **Tangent space**: Ensure all calculations are in the same space
3. **Normal map format**: Use compressed normal maps for mobile
4. **Seams**: Ensure tangents are consistent across mesh boundaries

## 🧪 Exercises

1. **Parallax mapping**: Extend normal mapping with parallax
2. **Anisotropic filtering**: Use anisotropic filtering for better normal map quality
3. **Normal map generation**: Generate normal maps from height maps

## 📚 References

- [LearnOpenGL - Normal Mapping](https://learnopengl.com/Advanced-Lighting/Normal-Mapping)
