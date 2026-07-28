# TargetCamera Class Documentation

The `TargetCamera` class is an orbit-style camera designed for interactive 3D environments. It allows the camera to revolve around a target point, zoom in/out, pan, and roll, making it ideal for inspecting models or scenes.

## Overview

`TargetCamera` inherits from the base `Camera` class and extends it with sophisticated rotation and movement logic based on quaternions. It is specifically designed to handle touch and mouse input directly through dedicated event handlers.

### Key Concepts

-   **Target Point**: The central point the camera looks at (`m_targetPosition`).
-   **Radius**: The distance between the camera and the target (`m_radius`).
-   **Orientation**: Managed using a quaternion (`m_targetRotation`), providing smooth, gimbal-lock-free rotation.

---

## Public Methods

### Configuration & State

#### `void setRadius(float mRadius)`
Sets the distance from the camera to the target.

#### `float getRadius() const`
Returns the current distance from the camera to the target.

#### `void setTargetPosition(const glm::vec3 &targetPosition)`
Sets the world-space coordinate of the point the camera should look at.

#### `void setTargetRotation(const glm::quat &targetRotation)`
Directly sets the camera's orientation using a quaternion.

#### `const glm::quat &getTargetRotation() const`
Returns the current orientation quaternion.

#### `glm::mat4 getTargetTransform() const`
Returns a transformation matrix representing the target's position and orientation.

#### `void setTargetTransform(const glm::mat4 &targetTransform)`
Sets both the target position and orientation from a single 4x4 matrix.

---

### Operations

#### `void update()`
Recalculates the view and projection matrices. This should be called every frame before rendering. It only performs calculations if state changes have occurred (lazy evaluation).

#### `void reset()`
Resets the camera to its default position, orientation, radius, and FOV.

#### `float calculateScaleFactor(const float &distanceFromCamera, const float &desiredObjectSize) const`
Calculates a scaling factor to make an object appear at a specific size on the screen relative to its distance from the camera.

---

### Event Handlers (Interaction)

These methods are designed to be called by input systems (e.g., Android touch events).

#### `void onSingleTouching(glm::vec2 prevPoint, glm::vec2 point)`
Handles rotation (Orbit).
-   **Logic**: Calculates a perpendicular vector to the drag direction and rotates the camera around that axis.

#### `void onDoubleTouching(glm::vec2 prevPoint0, glm::vec2 point0, glm::vec2 prevPoint1, glm::vec2 point1)`
Handles complex multi-touch gestures:
1.  **Zooming**: Based on the change in distance between the two points (Pinch-to-zoom).
2.  **Rolling**: Based on the change in angle between the two points.
3.  **Panning**: Based on the average translation of both points.

#### `void move(const glm::vec2 &move)`
Moves the target point in the camera's local XY plane (Panning).

#### `void zoom(const float &zoom)`
Adjusts the radius. A value > 1 zooms out, while < 1 zooms in. The radius is clamped between 2.0 and 50.0 units.

#### `void roll(const float &angle)`
Rotates the camera around its local forward axis (the Z-axis looking from camera to target).

---

## Usage Example

```cpp
// 1. Initialization
TargetCamera* m_camera = new TargetCamera();
m_camera->setRadius(10.0f);
m_camera->setTargetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

// 2. Handling Interaction (inside an event callback)
void onTouch(float x, float y) {
    m_camera->onSingleTouching(m_lastTouch, glm::vec2(x, y));
}

// 3. Main Loop
void onDraw() {
    m_camera->update();
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 projection = m_camera->getProjectionMatrix();
    
    // Use matrices in shaders...
}
```
