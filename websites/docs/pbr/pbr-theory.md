---
sidebar_position: 4
title: PBR Theory
---

# PBR Theory

Physically Based Rendering (PBR) simulates how light interacts with materials in a physically accurate way.

## 📋 Overview

In this tutorial, you will learn:

- What PBR is and why it's used
- The Cook-Torrance BRDF
- Physical material properties
- How PBR differs from traditional lighting models

## 🔑 Key Concepts

### BRDF (Bidirectional Reflectance Distribution Function)

The BRDF describes how light reflects from a surface:

```
f(l, v) = diffuse + specular
```

### Cook-Torrance BRDF

The Cook-Torrance model includes:
- **Diffuse term**: Lambertian reflection
- **Specular term**: Microfacet-based reflection

### Material Properties

PBR materials use:
- **Albedo**: Base color
- **Metallic**: Metalness (0 = dielectric, 1 = metal)
- **Roughness**: Surface roughness (0 = smooth, 1 = rough)
- **AO**: Ambient occlusion

## 🧮 Mathematical Background

### Lambertian Diffuse

```
diffuse = albedo / PI
```

### Cook-Torrance Specular

```
specular = D * F * G / (4 * (n · l) * (n · v))
```

Where:
- **D**: Normal distribution function (GGX/Trowbridge-Reitz)
- **F**: Fresnel equation (Schlick approximation)
- **G**: Geometry function (Smith's method)

### GGX Distribution

```
D = roughness^2 / (PI * ((n · h)^2 * (roughness^2 - 1) + 1)^2)
```

### Schlick Fresnel

```
F = F0 + (1 - F0) * (1 - (h · v))^5
```

Where F0 is the Fresnel reflectance at normal incidence.

### Smith Geometry

```
G = G1(l) * G1(v)
G1(x) = 2 * (n · x) / ((n · x) + sqrt(roughness^2 + (1 - roughness^2) * (n · x)^2))
```

## 📝 Code Walkthrough

### PBR Fragment Shader

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

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 camPos;

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);

void main() {
    vec3 albedo = pow(texture(albedoMap, fs_in.TexCoords).rgb, 2.2);
    float metallic = texture(metallicMap, fs_in.TexCoords).r;
    float roughness = texture(roughnessMap, fs_in.TexCoords).r;
    float ao = texture(aoMap, fs_in.TexCoords).r;
    
    vec3 N = normalize(fs_in.Normal);
    vec3 V = normalize(camPos - fs_in.WorldPos);
    
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);
    
    vec3 Lo = vec3(0.0);
    
    vec3 L = normalize(lightPos - fs_in.WorldPos);
    vec3 H = normalize(V + L);
    float distance = length(lightPos - fs_in.WorldPos);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = lightColor * attenuation;
    
    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    
    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001;
    vec3 specular = numerator / denominator;
    
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;
    
    float NdotL = max(dot(N, L), 0.0);
    Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;
    
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));
    
    FragColor = vec4(color, 1.0);
}
```

## 🎮 Interactive Demo

In the app, see physically accurate materials with PBR.

## ⚠️ Common Pitfalls

1. **Gamma correction**: PBR requires linear space calculations
2. **F0 values**: Use correct Fresnel values for different materials
3. **Energy conservation**: Ensure diffuse + specular `<=` 1
4. **Roughness range**: Roughness should be in [0, 1]

## 🧪 Exercises

1. **Material editor**: Create a tool to adjust PBR material parameters
2. **Anisotropic PBR**: Implement anisotropic roughness
3. **Clear coat**: Add clear coat layer for car paint effects

## 📚 References

- [LearnOpenGL - PBR Theory](https://learnopengl.com/PBR/Theory)
