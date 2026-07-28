---
sidebar_position: 7
title: Shadow Mapping
---

# Shadow Mapping

Shadow mapping generates real-time shadows by rendering the scene from the light's perspective.

## 📋 Overview

In this tutorial, you will learn:

- How shadow mapping works
- How to implement shadow mapping
- How to handle shadow artifacts
- How to optimize shadow mapping

## 🔑 Key Concepts

### Shadow Mapping Pipeline

1. **Depth pass**: Render scene from light's perspective, store depth in shadow map
2. **Render pass**: Render scene normally, compare fragment depth with shadow map

### Shadow Map

A texture that stores the depth from the light's perspective:
- 2D texture for directional lights
- Cube map for point lights

### Shadow Comparison

For each fragment:
1. Transform fragment position to light space
2. Compare fragment depth with shadow map depth
3. If fragment is behind shadow map depth, it's in shadow

## 🧮 Mathematical Background

### Light Space Transformation

```
light_space_position = light_projection * light_view * model * vertex_position
```

### Depth Comparison

```
shadow_map_depth = texture(shadowMap, light_space_position.xy).r
fragment_depth = light_space_position.z

if (fragment_depth > shadow_map_depth + bias):
    fragment is in shadow
else:
    fragment is lit
```

### Shadow Bias

Shadow bias prevents "shadow acne":
```
bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005)
```

## 📝 Code Walkthrough

### Depth Pass

```cpp
// Bind shadow map framebuffer
glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
glClear(GL_DEPTH_BUFFER_BIT);

// Use depth shader
depthShader->use();

// Set light space matrices
depthShader->setMat4("lightProjection", lightProjection);
depthShader->setMat4("lightView", lightView);

// Render scene
renderScene(depthShader);

// Unbind framebuffer
glBindFramebuffer(GL_FRAMEBUFFER, 0);
```

### Shadow Comparison in Shader

```glsl
float ShadowCalculation(vec4 fragPosLightSpace) {
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    
    return shadow;
}
```

## 🎮 Interactive Demo

In the app, see real-time shadows in action.

## ⚠️ Common Pitfalls

1. **Shadow acne**: Use shadow bias to prevent self-shadowing
2. **Peter panning**: Too much bias causes shadows to detach from objects
3. **Shadow map resolution**: Low resolution causes pixelated shadows
4. **Depth precision**: Use higher precision shadow maps

## 🧪 Exercises

1. **Soft shadows**: Implement PCF (Percentage Closer Filtering)
2. **Variance shadow mapping**: Implement VSM for smoother shadows
3. **Cascaded shadows**: Implement CSM for large scenes

## 📚 References

- [LearnOpenGL - Shadow Mapping](https://learnopengl.com/Advanced-Lighting/Shadow-Mapping)
