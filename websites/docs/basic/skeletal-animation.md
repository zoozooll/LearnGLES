---
sidebar_position: 13
title: Skeletal Animation
---

# Skeletal Animation

Skeletal animation uses a hierarchy of bones to animate 3D models realistically.

## 📋 Overview

In this tutorial, you will learn:

- What skeletal animation is and how it works
- How to load animated models with Assimp
- How to implement bone hierarchies
- How to animate models in real-time

## 🔑 Key Concepts

### Bone Hierarchy

A skeleton consists of bones arranged in a hierarchy:

- **Root bone**: Top-level bone (e.g., hips)
- **Child bones**: Connected to parent bones (e.g., spine, arms)
- **Leaf bones**: End of the hierarchy (e.g., fingers)

### Animation Data

Each animation contains:

- **Keyframes**: Position, rotation, and scale at specific times
- **Bone transformations**: How each bone moves over time
- **Duration**: Total length of the animation

## 🧮 Mathematical Background

### Bone Transformations

Each bone has several transformation matrices:

1. **Bind Pose**: Rest position of the bone
2. **Offset Matrix**: Transforms from bone space to model space
3. **Animation Matrix**: Current transformation based on keyframe
4. **Final Transformation**: Combined transformation for rendering

```
Final = Animation × Offset × InverseBindPose
```

### Linear Interpolation

Between keyframes, we interpolate:

```
value = (1 - t) * value_prev + t * value_next
```

## 📝 Code Walkthrough

### Loading Animation Data

```cpp
class Animator {
public:
    void UpdateAnimation(float dt);
    std::map<std::string, glm::mat4> GetFinalBoneMatrices();
    
private:
    Animation* currentAnimation;
    float currentTime;
};
```

### Applying Bone Transformations

In the vertex shader:

```glsl
#version 320 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in ivec4 aBoneIds;
layout (location = 4) in vec4 aWeights;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 boneMatrices[100];

void main() {
    vec4 totalPos = vec4(0.0f);
    
    for(int i = 0; i < 4; i++) {
        if(aBoneIds[i] == -1) continue;
        if(aBoneIds[i] >= 100) continue;
        
        vec4 localPos = boneMatrices[aBoneIds[i]] * vec4(aPos, 1.0);
        totalPos += localPos * aWeights[i];
    }
    
    gl_Position = projection * view * model * totalPos;
}
```

## 🎮 Interactive Demo

In the app, watch animated characters move with realistic bone-based animation.

## ⚠️ Common Pitfalls

1. **Bone limit**: Too many bones can exceed uniform limits
2. **Weight normalization**: Weights must sum to 1.0
3. **Animation blending**: Multiple animations need proper blending
4. **Performance**: Skeletal animation is computationally expensive

## 🧪 Exercises

1. **Animation blending**: Blend between two animations (e.g., walk to run)
2. **Inverse kinematics**: Implement IK for realistic limb movement
3. **Procedural animation**: Generate animations procedurally

## 📚 References

- [Assimp Skeletal Animation](https://assimp-docs.readthedocs.io/en/latest/usage/animation.html)
- [LearnOpenGL - Skeletal Animation](https://learnopengl.com/Advanced-Animation/Skeletal-Animation)
