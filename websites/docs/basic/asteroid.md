---
sidebar_position: 11
title: Asteroid
---

# Asteroid Field

This tutorial demonstrates practical instancing by rendering a field of asteroids.

## 📋 Overview

In this tutorial, you will learn:

- How to create procedural asteroid geometry
- How to use instancing for large scenes
- How to add variation to instances
- Performance optimization techniques

## 🔑 Key Concepts

### Procedural Geometry

Asteroids are generated procedurally by:

1. Starting with an icosahedron (20-sided sphere)
2. Subdividing faces to increase detail
3. Displacing vertices using noise functions

### Instance Variation

Each asteroid instance has:

- Unique position
- Unique rotation
- Unique scale
- Unique color/texture offset

## 🧮 Mathematical Background

### Icosahedron Subdivision

Each triangular face is subdivided into four smaller triangles:

```
A ---- B
| \  / |
|  C   |
| /  \ |
D ---- E
```

New vertices are created at midpoints and displaced.

## 📝 Code Walkthrough

### Generating Asteroid Geometry

```cpp
std::vector<glm::vec3> generateAsteroid(int subdivisions, float displacement) {
    std::vector<glm::vec3> vertices = createIcosahedron();
    
    for (int i = 0; i < subdivisions; i++) {
        vertices = subdivide(vertices);
    }
    
    // Displace vertices
    for (auto& v : vertices) {
        v += glm::normalize(v) * noise(v) * displacement;
    }
    
    return vertices;
}
```

### Instanced Rendering Setup

```cpp
// Create instance data
std::vector<glm::mat4> modelMatrices;
for (unsigned int i = 0; i < asteroidCount; i++) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, randomPosition());
    model = glm::rotate(model, randomAngle(), randomAxis());
    model = glm::scale(model, glm::vec3(randomScale()));
    modelMatrices.push_back(model);
}

// Set up instanced attribute for model matrices
glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), 
             &modelMatrices[0], GL_STATIC_DRAW);
```

## 🎮 Interactive Demo

In the app, fly through an asteroid field with hundreds of unique asteroids.

## ⚠️ Common Pitfalls

1. **Memory usage**: Too many instances can exceed memory limits
2. **Triangle count**: High subdivision increases triangle count
3. **Uniform buffer size**: Model matrices may exceed uniform buffer limits

## 🧪 Exercises

1. **Asteroid collision**: Add collision detection between asteroids
2. **Dynamic asteroids**: Make asteroids move over time
3. **LOD system**: Use different mesh detail levels based on distance

## 📚 References

- [LearnOpenGL - Asteroids](https://learnopengl.com/Advanced-OpenGL/Instancing/Asteroids)
