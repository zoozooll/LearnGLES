---
sidebar_position: 6
title: IBL (Image-Based Lighting)
---

# IBL (Image-Based Lighting)

Image-Based Lighting uses HDR environment maps to provide realistic lighting.

## 📋 Overview

In this tutorial, you will learn:

- What IBL is and why it's used
- How to create irradiance maps
- How to create prefilter maps
- How to implement IBL in PBR

## 🔑 Key Concepts

### IBL Pipeline

1. **Load HDR environment map**
2. **Generate irradiance map**: Diffuse lighting from environment
3. **Generate prefilter map**: Specular lighting for different roughness levels
4. **Generate BRDF lookup texture**: Precomputed Fresnel/geometry terms

### Irradiance Map

An irradiance map is a low-resolution cubemap that approximates indirect diffuse lighting.

### Prefilter Map

A mipmapped cubemap where each mip level corresponds to a different roughness level.

### BRDF LUT

A 2D texture that stores precomputed BRDF values for different N·V and roughness combinations.

## 🧮 Mathematical Background

### Irradiance Calculation

```
E = (1 / PI) * integral(environment * cos(theta) * domega)
```

This is approximated by convolving the environment map with a cosine-weighted hemisphere.

### Prefiltering

For each roughness level, the environment map is filtered:

```
filtered = integral(environment * D * F * G * cos(theta) * domega)
```

## 📝 Code Walkthrough

### Generating Irradiance Map

```cpp
void generateIrradianceMap(unsigned int environmentMap, unsigned int irradianceMap) {
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    
    for (unsigned int i = 0; i < 6; i++) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                              GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Render full-screen quad with irradiance shader
        renderQuad();
    }
}
```

### IBL Shader

```glsl
#version 320 es
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
    vec3 WorldPos;
    vec3 Normal;
} fs_in;

uniform sampler2D albedoMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;

uniform vec3 camPos;

void main() {
    vec3 albedo = pow(texture(albedoMap, fs_in.TexCoords).rgb, 2.2);
    float metallic = texture(metallicMap, fs_in.TexCoords).r;
    float roughness = texture(roughnessMap, fs_in.TexCoords).r;
    float ao = texture(aoMap, fs_in.TexCoords).r;
    
    vec3 N = normalize(fs_in.Normal);
    vec3 V = normalize(camPos - fs_in.WorldPos);
    vec3 R = reflect(-V, N);
    
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);
    
    // Diffuse IBL
    vec3 irradiance = texture(irradianceMap, N).rgb;
    vec3 diffuse = irradiance * albedo;
    
    // Specular IBL
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilterMap, R, roughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (F0 * brdf.x + brdf.y);
    
    vec3 kS = fresnelSchlick(max(dot(N, V), 0.0), F0);
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;
    
    vec3 ambient = (kD * diffuse + specular) * ao;
    
    // ... direct lighting calculation
    
    vec3 color = ambient + directLighting;
    
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));
    
    FragColor = vec4(color, 1.0);
}
```

## 🎮 Interactive Demo

In the app, see realistic environment lighting with IBL.

## ⚠️ Common Pitfalls

1. **HDR format**: Use floating-point textures for HDR
2. **Cube map order**: Ensure cubemap faces are in correct order
3. **Lod bias**: Correctly map roughness to mip levels
4. **Gamma correction**: IBL requires linear space

## 🧪 Exercises

1. **Dynamic IBL**: Generate irradiance map from scene at runtime
2. **Multiple environments**: Allow users to switch between different HDR environments
3. **Custom BRDF**: Implement custom BRDF functions

## 📚 References

- [LearnOpenGL - IBL](https://learnopengl.com/PBR/IBL/Diffuse-Irradiance)
