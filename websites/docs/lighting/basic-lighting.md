---
sidebar_position: 2
title: Basic Lighting
---

# Basic Lighting

Basic lighting introduces the fundamental concepts of lighting models in computer graphics.

## 📋 Overview

In this tutorial, you will learn:

- The Phong lighting model
- The Blinn-Phong lighting model
- How to implement ambient, diffuse, and specular lighting
- How lighting affects the appearance of 3D objects

## 🔑 Key Concepts

### Phong Lighting Model

The Phong model calculates lighting in three components:

1. **Ambient**: Base illumination, simulating indirect light
2. **Diffuse**: Directional light based on surface normal
3. **Specular**: Shiny highlight based on view direction

### Blinn-Phong Lighting Model

Blinn-Phong simplifies the specular calculation by using the halfway vector instead of the reflection vector:

- **Halfway vector**: `H = normalize(L + V)`
- **Specular**: `max(dot(N, H), 0)^shininess`

## 🧮 Mathematical Background

### Ambient Lighting

```
ambient = ambient_color * ambient_intensity
```

### Diffuse Lighting

```
diffuse = light_color * max(dot(N, L), 0)
```

Where:
- `N`: Surface normal (normalized)
- `L`: Light direction (from surface to light, normalized)

### Specular Lighting (Phong)

```
R = 2 * dot(N, L) * N - L
specular = light_color * max(dot(R, V), 0)^shininess
```

Where:
- `R`: Reflection direction
- `V`: View direction (from surface to camera, normalized)

### Specular Lighting (Blinn-Phong)

```
H = normalize(L + V)
specular = light_color * max(dot(N, H), 0)^shininess
```

## 📝 Code Walkthrough

### Lighting Shader

```glsl
#version 320 es
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
```

## 🎮 Interactive Demo

In the app, observe how lighting changes the appearance of objects.

## ⚠️ Common Pitfalls

1. **Normal normalization**: Always normalize normals in the shader
2. **Light direction**: Ensure light direction is from surface to light
3. **Shininess**: High shininess values produce smaller highlights
4. **Gamma correction**: Colors may appear too dark without gamma correction

## 🧪 Exercises

1. **Animated light**: Make the light move around the scene
2. **Color changing**: Change light and object colors dynamically
3. **Multiple objects**: Apply lighting to multiple objects with different materials

## 📚 References

- [LearnOpenGL - Basic Lighting](https://learnopengl.com/Lighting/Basic-Lighting)
