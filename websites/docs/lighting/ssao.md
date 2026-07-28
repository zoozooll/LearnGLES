---
sidebar_position: 10
title: SSAO
---

# SSAO (Screen-Space Ambient Occlusion)

SSAO adds realistic contact shadows by approximating ambient occlusion in screen space.

## 📋 Overview

In this tutorial, you will learn:

- What SSAO is and why it's used
- How to implement SSAO
- Noise textures for random sampling
- Blurring SSAO results

## 🔑 Key Concepts

### SSAO Algorithm

1. **Render normal and depth**: Store view-space normals and depth
2. **Sample hemisphere**: For each pixel, sample random points in hemisphere around normal
3. **Compare depths**: Count samples that are closer than current pixel
4. **Blur**: Apply blur to reduce noise
5. **Combine**: Multiply SSAO with ambient lighting

### Noise Texture

A small noise texture provides random directions for sampling.

### Kernel

A set of random vectors in a hemisphere for sampling.

## 🧮 Mathematical Background

### Hemisphere Sampling

For each fragment:
1. Create tangent space basis from normal
2. Transform kernel samples to tangent space
3. Sample depth at transformed positions
4. Compare with current depth

### Occlusion Calculation

```
occlusion = count(closer_samples) / total_samples
ambient *= (1 - occlusion)
```

## 📝 Code Walkthrough

### Creating Noise Texture

```cpp
std::vector<glm::vec3> ssaoNoise;
for (unsigned int i = 0; i < 64; i++) {
    glm::vec3 noise(
        glm::random(-1.0f, 1.0f),
        glm::random(-1.0f, 1.0f),
        0.0f
    );
    noise = glm::normalize(noise);
    ssaoNoise.push_back(noise);
}

// Create noise texture
glGenTextures(1, &noiseTexture);
glBindTexture(GL_TEXTURE_2D, noiseTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 8, 8, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
```

### SSAO Shader

```glsl
#version 320 es
out float FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D texNoise;

uniform vec3 samples[64];
uniform int sampleCount;
uniform float radius;

void main() {
    vec3 fragPos = texture(gPosition, TexCoords).xyz;
    vec3 normal = texture(gNormal, TexCoords).xyz;
    vec3 randomVec = texture(texNoise, TexCoords * 8.0).xyz;
    
    // Create TBN matrix
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);
    
    float occlusion = 0.0;
    for (int i = 0; i < sampleCount; i++) {
        vec3 samplePos = TBN * samples[i];
        samplePos = fragPos + samplePos * radius;
        
        vec4 offset = vec4(samplePos, 1.0);
        offset = projection * offset;
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 + 0.5;
        
        float sampleDepth = texture(gPosition, offset.xy).z;
        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samplePos.z + 0.025 ? 1.0 : 0.0) * rangeCheck;
    }
    
    occlusion = 1.0 - (occlusion / sampleCount);
    FragColor = occlusion;
}
```

## 🎮 Interactive Demo

In the app, see realistic contact shadows with SSAO.

## ⚠️ Common Pitfalls

1. **Performance**: SSAO is computationally expensive
2. **Noise**: Without blurring, SSAO can be noisy
3. **Radius**: Too large = dark corners, too small = no effect
4. **Z-fighting**: Use bias to prevent self-occlusion

## 🧪 Exercises

1. **SSAO quality**: Allow users to adjust sample count
2. **SSAO radius**: Allow users to adjust radius
3. **SSAO+**: Implement enhanced SSAO with better quality

## 📚 References

- [LearnOpenGL - SSAO](https://learnopengl.com/Advanced-Lighting/SSAO)
