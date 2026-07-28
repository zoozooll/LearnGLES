---
sidebar_position: 4
title: Phong vs Blinn
---

# Phong vs Blinn

This tutorial compares the Phong and Blinn-Phong lighting models.

## 📋 Overview

In this tutorial, you will learn:

- The difference between Phong and Blinn-Phong
- When to use each model
- Performance considerations
- Visual differences between the two models

## 🔑 Key Concepts

### Phong Lighting

Phong uses the reflection vector:

- More accurate physically
- Calculates `reflect(-L, N)`
- Slightly more expensive

### Blinn-Phong Lighting

Blinn-Phong uses the halfway vector:

- Faster to compute
- Calculates `normalize(L + V)`
- Visually similar but not identical

## 🧮 Mathematical Background

### Reflection Vector (Phong)

```
R = 2 * dot(N, L) * N - L
```

This reflects the light direction across the normal.

### Halfway Vector (Blinn-Phong)

```
H = normalize(L + V)
```

This is the vector halfway between the light and view directions.

### Comparison

| Property | Phong | Blinn-Phong |
|----------|-------|-------------|
| Accuracy | More accurate | Approximation |
| Performance | Slightly slower | Faster |
| Specular Highlight | Sharper | Softer |
| GPU Support | Requires reflection | Simpler calculation |

## 📝 Code Walkthrough

### Phong Specular

```glsl
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
```

### Blinn-Phong Specular

```glsl
vec3 halfwayDir = normalize(lightDir + viewDir);
float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
```

## 🎮 Interactive Demo

In the app, compare Phong and Blinn-Phong side by side.

## ⚠️ Common Pitfalls

1. **Shininess values**: Blinn-Phong may need different shininess values than Phong
2. **Normalization**: Always normalize vectors before dot product
3. **View direction**: Ensure view direction is from surface to camera

## 🧪 Exercises

1. **Hybrid model**: Combine Phong and Blinn-Phong for different materials
2. **Anisotropic specular**: Implement anisotropic specular highlights
3. **Comparison tool**: Create a tool to compare different lighting models

## 📚 References

- [LearnOpenGL - Blinn-Phong](https://learnopengl.com/Lighting/Basic-Lighting)
