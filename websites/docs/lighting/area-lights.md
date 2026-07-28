---
sidebar_position: 11
title: Area Lights
---

# Area Lights

Area lights simulate light from rectangular sources, creating more realistic soft shadows.

## 📋 Overview

In this tutorial, you will learn:

- What area lights are and why they're used
- How to implement area lights
- Monte Carlo sampling for soft shadows
- Performance considerations

## 🔑 Key Concepts

### Area Light

An area light is a rectangular light source:
- Has position, size, and orientation
- Emits light from its entire surface
- Creates soft shadows with penumbra

### Soft Shadows

Soft shadows have:
- **Umbra**: Dark center
- **Penumbra**: Soft edge
- **Antumbra**: Area behind the shadow

### Monte Carlo Sampling

Instead of sampling every point on the light, we randomly sample a few points:
- More samples = better quality
- Fewer samples = faster performance

## 🧮 Mathematical Background

### Area Light Sampling

To sample a point on the area light:

```
point = position + u * width + v * height
```

Where u and v are random values between 0 and 1.

### Light Contribution

For each sample:
1. Calculate light direction from fragment to sample point
2. Calculate distance and attenuation
3. Check if sample is visible (shadow check)
4. Accumulate contribution

## 📝 Code Walkthrough

### Area Light Struct

```glsl
struct AreaLight {
    vec3 position;
    vec3 width;
    vec3 height;
    vec3 color;
    float intensity;
};
```

### Area Light Calculation

```glsl
vec3 CalculateAreaLight(AreaLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 result = vec3(0.0);
    
    // Number of samples
    int samples = 4;
    
    for (int i = 0; i < samples; i++) {
        // Random sample on the area light
        float u = random(vec2(i, gl_FragCoord.x));
        float v = random(vec2(i, gl_FragCoord.y));
        
        vec3 lightPos = light.position + u * light.width + v * light.height;
        vec3 lightDir = normalize(lightPos - fragPos);
        
        // Shadow check
        float shadow = ShadowCalculation(fragPos, lightDir);
        if (shadow > 0.9) continue;
        
        // Diffuse
        float diff = max(dot(normal, lightDir), 0.0);
        
        // Specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
        
        // Attenuation
        float distance = length(lightPos - fragPos);
        float area = length(cross(light.width, light.height));
        float attenuation = area / (distance * distance);
        
        result += (diff + spec) * light.color * light.intensity * attenuation;
    }
    
    return result / float(samples);
}
```

## 🎮 Interactive Demo

In the app, see soft shadows from area lights.

## ⚠️ Common Pitfalls

1. **Performance**: Monte Carlo sampling is expensive
2. **Sample count**: Too few = noisy shadows, too many = slow
3. **Light size**: Larger lights = softer shadows
4. **Attenuation**: Area lights use inverse square law with area factor

## 🧪 Exercises

1. **Sample count adjustment**: Allow users to adjust sample count
2. **Light shape**: Implement circular or spherical area lights
3. **Importance sampling**: Use importance sampling for better quality

## 📚 References

- [LearnOpenGL - Area Lights](https://learnopengl.com/Advanced-Lighting/Area-Lights)
