---
sidebar_position: 6
title: Multiple Lights
---

# Multiple Lights

Multiple lights create more complex and realistic lighting scenarios.

## 📋 Overview

In this tutorial, you will learn:

- How to handle multiple light sources
- How to combine different light types
- Performance considerations
- Realistic scene lighting

## 🔑 Key Concepts

### Light Accumulation

When multiple lights affect a surface, their contributions are summed:

```
final_color = sum(light_contribution) for all lights
```

### Light Types

Combine different light types:
- Directional lights (sun)
- Point lights (lamps)
- Spotlights (flashlights)

### Performance

Each additional light increases shader complexity. Techniques to optimize:
- Light culling (only process lights affecting the object)
- Light baking (precompute static lighting)
- Deferred rendering (render lights as full-screen passes)

## 🧮 Mathematical Background

### Light Contribution

For each light, calculate its contribution:

```
contribution = ambient + diffuse + specular
```

Where each component depends on the light type.

### Light Culling

Check if a light affects a fragment:
- Directional lights always affect all fragments
- Point lights only affect fragments within range
- Spotlights only affect fragments within cone

## 📝 Code Walkthrough

### Multiple Lights in Shader

```glsl
struct PointLight {
    vec3 position;
    vec3 color;
    float radius;
};

#define MAX_LIGHTS 10
uniform PointLight pointLights[MAX_LIGHTS];
uniform int lightCount;

vec3 calculateLighting(vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 result = vec3(0.0);
    
    // Directional light
    result += calcDirLight(dirLight, normal, viewDir);
    
    // Point lights
    for (int i = 0; i < lightCount; i++) {
        float distance = length(pointLights[i].position - fragPos);
        if (distance < pointLights[i].radius) {
            result += calcPointLight(pointLights[i], normal, fragPos, viewDir);
        }
    }
    
    // Spotlights
    result += calcSpotLight(spotLight, normal, fragPos, viewDir);
    
    return result;
}
```

### Setting Up Lights in C++

```cpp
// Set light count
shader->setInt("lightCount", pointLights.size());

// Set each light's properties
for (unsigned int i = 0; i < pointLights.size(); i++) {
    std::string name = "pointLights[" + std::to_string(i) + "]";
    shader->setVec3(name + ".position", pointLights[i].position);
    shader->setVec3(name + ".color", pointLights[i].color);
    shader->setFloat(name + ".radius", pointLights[i].radius);
}
```

## 🎮 Interactive Demo

In the app, see how multiple lights illuminate the scene.

## ⚠️ Common Pitfalls

1. **Light limit**: GPU has limits on uniform array size
2. **Performance**: Too many lights can reduce FPS
3. **Light intensity**: Multiple lights can overexpose the scene
4. **Light order**: Process most important lights first

## 🧪 Exercises

1. **Dynamic lights**: Add/remove lights at runtime
2. **Light priority**: Implement light priority system
3. **Light linking**: Only process lights that affect each object

## 📚 References

- [LearnOpenGL - Multiple Lights](https://learnopengl.com/Lighting/Multiple-lights)
