---
sidebar_position: 16
title: Frustum Culling
---

# Frustum Culling

Frustum culling optimizes rendering by skipping objects outside the camera's view.

## 📋 Overview

In this tutorial, you will learn:

- What the view frustum is
- How to check if objects are inside the frustum
- Different frustum culling techniques
- Performance benefits of frustum culling

## 🔑 Key Concepts

### View Frustum

The view frustum is a pyramid-shaped volume that defines what the camera can see:

- **Near plane**: Closest visible distance
- **Far plane**: Farthest visible distance
- **Left/Right planes**: Sides of the frustum
- **Top/Bottom planes**: Top and bottom of the frustum

### Bounding Volumes

Objects are represented by bounding volumes:

- **AABB (Axis-Aligned Bounding Box)**: Fast to test, but inaccurate
- **OBB (Oriented Bounding Box)**: More accurate, slower
- **Bounding Sphere**: Fast, good for roughly spherical objects

## 🧮 Mathematical Background

### Plane Equation

Each frustum plane is defined by:

```
ax + by + cz + d = 0
```

Where (a, b, c) is the plane normal pointing inward.

### Point-Plane Distance

The distance from a point to a plane:

```
distance = ax + by + cz + d
```

If distance > 0, the point is inside the frustum.

### Sphere-Plane Test

For a sphere with center (cx, cy, cz) and radius r:

```
distance = a*cx + b*cy + c*cz + d
if (distance < -r): sphere is outside
if (abs(distance) <= r): sphere intersects plane
if (distance > r): sphere is inside
```

## 📝 Code Walkthrough

### Extracting Frustum Planes

```cpp
void extractFrustumPlanes(const glm::mat4& projView, std::vector<glm::vec4>& planes) {
    // Left plane
    planes[0] = projView[3] + projView[0];
    // Right plane
    planes[1] = projView[3] - projView[0];
    // Bottom plane
    planes[2] = projView[3] + projView[1];
    // Top plane
    planes[3] = projView[3] - projView[1];
    // Near plane
    planes[4] = projView[3] + projView[2];
    // Far plane
    planes[5] = projView[3] - projView[2];
    
    // Normalize planes
    for (auto& plane : planes) {
        float len = glm::length(glm::vec3(plane));
        plane /= len;
    }
}
```

### Frustum Culling Test

```cpp
bool isSphereInFrustum(const glm::vec3& center, float radius, 
                       const std::vector<glm::vec4>& planes) {
    for (const auto& plane : planes) {
        float distance = glm::dot(glm::vec3(plane), center) + plane.w;
        if (distance < -radius) {
            return false;
        }
    }
    return true;
}
```

## 🎮 Interactive Demo

In the app, observe how objects are culled when moving the camera.

## ⚠️ Common Pitfalls

1. **Plane extraction**: Ensure planes are extracted correctly from the projection-view matrix
2. **Bounding volume accuracy**: Too loose = no culling, too tight = false culling
3. **Performance overhead**: Culling itself has overhead; only cull if there are many objects

## 🧪 Exercises

1. **AABB culling**: Implement AABB-frustum intersection
2. **Hierarchical culling**: Use octree or BVH for large scenes
3. **Combined culling**: Combine frustum culling with occlusion culling

## 📚 References

- [LearnOpenGL - Frustum Culling](https://learnopengl.com/Advanced-OpenGL/Frustum-Culling)
- [Real-Time Rendering - Frustum Culling](https://www.realtimerendering.com/)
