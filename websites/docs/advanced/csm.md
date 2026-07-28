---
sidebar_position: 2
title: CSM (Cascaded Shadow Maps)
---

# CSM (Cascaded Shadow Maps)

CSM provides high-quality shadows for large-scale scenes by splitting the view frustum into multiple cascades.

## 📋 Overview

In this tutorial, you will learn:

- What CSM is and why it's used
- How to split the view frustum into cascades
- How to render shadows for each cascade
- How to blend between cascades

## 🔑 Key Concepts

### View Frustum Splitting

The view frustum is split into N cascades:
- **Near cascade**: Small area, high resolution
- **Far cascade**: Large area, lower resolution

### Cascade Projection Matrices

Each cascade has its own projection matrix that tightly fits the cascade's bounds.

### Shadow Blending

To avoid visible seams between cascades, smoothly blend between cascade boundaries.

## 🧮 Mathematical Background

### Frustum Splitting

Two common splitting strategies:

**Uniform splitting:**
```
split_i = near + (far - near) * i / N
```

**Logarithmic splitting:**
```
split_i = near * (far / near)^(i / N)
```

### Cascade Bounds

For each cascade, calculate the bounding box in light space:
1. Transform frustum corners to light space
2. Find min and max bounds
3. Create projection matrix that fits bounds

## 📝 Code Walkthrough

### CSM Setup

```cpp
void setupCSM(int numCascades) {
    float near = camera->getNear();
    float far = camera->getFar();
    
    for (int i = 0; i < numCascades; i++) {
        // Calculate split distance
        float split = near * pow(far / near, (float)(i + 1) / numCascades);
        
        // Calculate frustum corners for this cascade
        std::vector<glm::vec4> frustumCorners = getFrustumCorners(prevSplit, split);
        
        // Transform to light space
        std::vector<glm::vec4> lightSpaceCorners;
        for (auto& corner : frustumCorners) {
            lightSpaceCorners.push_back(lightView * corner);
        }
        
        // Calculate bounds
        glm::vec3 min = glm::vec3(FLT_MAX);
        glm::vec3 max = glm::vec3(-FLT_MAX);
        for (auto& corner : lightSpaceCorners) {
            min = glm::min(min, glm::vec3(corner));
            max = glm::max(max, glm::vec3(corner));
        }
        
        // Create projection matrix
        float cascadeWidth = max.x - min.x;
        float cascadeHeight = max.y - min.y;
        float cascadeDepth = max.z - min.z;
        
        cascades[i].projection = glm::ortho(min.x, max.x, min.y, max.y, min.z, max.z);
        cascades[i].lightSpaceMatrix = cascades[i].projection * lightView;
        cascades[i].splitDistance = split;
    }
}
```

### CSM Shader

```glsl
#version 320 es
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
    vec3 FragPos;
} fs_in;

uniform sampler2D shadowMaps[4];
uniform mat4 lightSpaceMatrices[4];
uniform float cascadeDistances[4];
uniform vec3 lightDir;

float ShadowCalculation(vec4 fragPosLightSpace, int cascadeIndex) {
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    
    float closestDepth = texture(shadowMaps[cascadeIndex], projCoords.xy).r;
    float currentDepth = projCoords.z;
    
    float bias = 0.005;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    
    return shadow;
}

void main() {
    float depth = length(fs_in.FragPos);
    
    // Determine which cascade this fragment belongs to
    int cascadeIndex = 0;
    for (int i = 0; i < 3; i++) {
        if (depth < cascadeDistances[i]) {
            break;
        }
        cascadeIndex++;
    }
    
    vec4 fragPosLightSpace = lightSpaceMatrices[cascadeIndex] * vec4(fs_in.FragPos, 1.0);
    float shadow = ShadowCalculation(fragPosLightSpace, cascadeIndex);
    
    // ... lighting calculation with shadow
}
```

## 🎮 Interactive Demo

In the app, see high-quality shadows for large scenes with CSM.

## ⚠️ Common Pitfalls

1. **Cascade count**: Too few = poor quality, too many = performance cost
2. **Split strategy**: Logarithmic splitting usually works better than uniform
3. **Seams**: Ensure smooth blending between cascades
4. **Projection fit**: Tight projection matrices improve shadow quality

## 🧪 Exercises

1. **Cascade count adjustment**: Allow users to adjust the number of cascades
2. **Split strategy**: Implement both uniform and logarithmic splitting
3. **Shadow filtering**: Add PCF filtering for softer shadows

## 📚 References

- [Cascaded Shadow Maps](https://developer.nvidia.com/gpugems/gpugems3/part-ii-lighting-and-shadows/chapter-10-cascaded-shadow-maps)
