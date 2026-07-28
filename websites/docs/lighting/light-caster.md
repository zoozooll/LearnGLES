---
sidebar_position: 3
title: Light Caster
---

# Light Caster

Light casters are different types of light sources that illuminate the scene.

## 📋 Overview

In this tutorial, you will learn:

- Different types of light sources (directional, point, spotlight)
- How to implement each light type
- How to handle multiple light sources
- How to create realistic lighting effects

## 🔑 Key Concepts

### Directional Light

Directional light comes from a distant source (like the sun):

- Parallel rays
- No attenuation
- Constant direction

### Point Light

Point light originates from a specific point in space:

- Rays spread in all directions
- Attenuation over distance
- Position in world space

### Spotlight

Spotlight emits light in a cone shape:

- Position and direction
- Cutoff angle
- Smooth edge (soft spotlight)

## 🧮 Mathematical Background

### Attenuation

Point lights and spotlights attenuate over distance:

```
attenuation = 1 / (constant + linear * distance + quadratic * distance^2)
```

Where:
- `constant`: Base attenuation (usually 1)
- `linear`: Linear falloff
- `quadratic`: Quadratic falloff

### Spotlight Cutoff

```
theta = angle between light direction and fragment direction
if (theta < cutoff): inside spotlight
else: outside spotlight
```

### Smooth Spotlight

```
intensity = (cos(theta) - cos(outer_cutoff)) / (cos(cutoff) - cos(outer_cutoff))
intensity = clamp(intensity, 0, 1)
```

## 📝 Code Walkthrough

### Light Struct

```glsl
struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
```

### Lighting Calculations

```glsl
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}
```

## 🎮 Interactive Demo

In the app, see different light types in action.

## ⚠️ Common Pitfalls

1. **Light direction**: Directional light direction is usually from the sun
2. **Attenuation values**: Too high = light disappears quickly, too low = light too bright
3. **Cutoff angles**: Expressed in radians, not degrees
4. **Performance**: Too many lights can reduce FPS

## 🧪 Exercises

1. **Dynamic lights**: Make lights move and change color
2. **Light switches**: Turn lights on/off interactively
3. **Custom light types**: Create area lights or spotlights with custom shapes

## 📚 References

- [LearnOpenGL - Light Casters](https://learnopengl.com/Lighting/Light-casters)
