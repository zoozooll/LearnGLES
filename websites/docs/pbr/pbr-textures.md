---
sidebar_position: 5
title: PBR Textures
---

# PBR Textures

PBR textures provide the material properties needed for physically based rendering.

## 📋 Overview

In this tutorial, you will learn:

- Different PBR texture types
- How to use PBR texture maps
- Texture coordinate handling
- How to create PBR textures

## 🔑 Key Concepts

### PBR Texture Maps

| Texture | Purpose |
|---------|---------|
| **Albedo** | Base color of the material |
| **Normal** | Surface normals for detail |
| **Metallic** | Metalness (0-1) |
| **Roughness** | Surface roughness (0-1) |
| **AO** | Ambient occlusion |
| **Height** | Height for parallax mapping |

### Texture Formats

- **sRGB**: For albedo maps (gamma encoded)
- **Linear**: For normal, metallic, roughness, AO maps

### Texture Packing

Some engines pack multiple maps into one texture:
- RGBA: Albedo
- RGB: Normal (B is packed separately)
- R: Metallic + Roughness (packed)

## 🧮 Mathematical Background

### Texture Sampling

```
albedo = texture(albedoMap, texCoords).rgb
metallic = texture(metallicMap, texCoords).r
roughness = texture(roughnessMap, texCoords).r
```

### Gamma Correction

```
albedo = pow(albedo, 2.2)  // Convert to linear space
```

## 📝 Code Walkthrough

### Loading PBR Textures

```cpp
unsigned int albedoMap = loadTexture("textures/pbr/gold/albedo.png", false, true);
unsigned int normalMap = loadTexture("textures/pbr/gold/normal.png", false, false);
unsigned int metallicMap = loadTexture("textures/pbr/gold/metallic.png", false, false);
unsigned int roughnessMap = loadTexture("textures/pbr/gold/roughness.png", false, false);
unsigned int aoMap = loadTexture("textures/pbr/gold/ao.png", false, false);
```

### Setting Texture Uniforms

```cpp
shader->use();
shader->setInt("albedoMap", 0);
shader->setInt("normalMap", 1);
shader->setInt("metallicMap", 2);
shader->setInt("roughnessMap", 3);
shader->setInt("aoMap", 4);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, albedoMap);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, normalMap);
glActiveTexture(GL_TEXTURE2);
glBindTexture(GL_TEXTURE_2D, metallicMap);
glActiveTexture(GL_TEXTURE3);
glBindTexture(GL_TEXTURE_2D, roughnessMap);
glActiveTexture(GL_TEXTURE4);
glBindTexture(GL_TEXTURE_2D, aoMap);
```

### PBR Material Struct

```glsl
struct Material {
    sampler2D albedo;
    sampler2D normal;
    sampler2D metallic;
    sampler2D roughness;
    sampler2D ao;
};
```

## 🎮 Interactive Demo

In the app, see different PBR materials like gold, grass, and plastic.

## ⚠️ Common Pitfalls

1. **Gamma correction**: Albedo maps need gamma correction
2. **Texture format**: Use correct format (sRGB vs linear)
3. **Missing textures**: Ensure all texture maps are loaded
4. **Texture coordinates**: Ensure UV mapping is correct

## 🧪 Exercises

1. **Texture switching**: Allow users to switch between different PBR materials
2. **Procedural textures**: Generate PBR textures procedurally
3. **Texture blending**: Blend between different PBR materials

## 📚 References

- [LearnOpenGL - PBR Textures](https://learnopengl.com/PBR/Theory)
