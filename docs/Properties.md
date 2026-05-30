# UI Properties Documentation

This document describes the common UI properties used in the application's control panels to interact with the OpenGLES renderer. These properties allow for real-time adjustments of rendering state through a Kotlin-based UI, communicating with the native side via event messages.

## Common Properties

### 1. Cull Face (`cullFace`)
Toggles back-face culling to optimize rendering by not drawing the back faces of polygons.

- **UI Component**: Checkbox
- **Data Type**: `Boolean`
- **Event Details**:
    - **Event ID**: `cullface_event`
    - **Payload**: `{"on": Boolean}`
- **Native Interaction**: Typically maps to `glEnable(GL_CULL_FACE)` or `glDisable(GL_CULL_FACE)`.

### 2. Depth Test (`depthTest`)
Toggles the depth testing mechanism, which determines if a pixel should be drawn based on its depth relative to existing pixels in the frame buffer.

- **UI Component**: Checkbox
- **Data Type**: `Boolean`
- **Event Details**:
    - **Event ID**: `depthtest_event`
    - **Payload**: `{"on": Boolean}`
- **Native Interaction**: Typically maps to `glEnable(GL_DEPTH_TEST)` or `glDisable(GL_DEPTH_TEST)`.

### 3. Depth Function (`depthFunc`)
Selects the comparison function used in the depth test.

- **UI Component**: Selector (Dropdown/Exposed Dropdown Menu)
- **Data Type**: `UInt` (Index)
- **Event Details**:
    - **Event ID**: `depthtest_func_event`
    - **Payload**: `{"func": Int}` (Index of the selected function)
- **Options**:
    | Index | Constant | Description |
    | :--- | :--- | :--- |
    | 0 | `GL_NEVER` | Never passes. |
    | 1 | `GL_LESS` | Passes if the incoming depth value is less than the stored depth value. (Default) |
    | 2 | `GL_EQUAL` | Passes if the incoming depth value is equal to the stored depth value. |
    | 3 | `GL_LEQUAL` | Passes if the incoming depth value is less than or equal to the stored depth value. |
    | 4 | `GL_GREATER` | Passes if the incoming depth value is greater than the stored depth value. |
    | 5 | `GL_NOTEQUAL` | Passes if the incoming depth value is not equal to the stored depth value. |
    | 6 | `GL_GEQUAL` | Passes if the incoming depth value is greater than or equal to the stored depth value. |
    | 7 | `GL_ALWAYS` | Always passes. |

---

## Technical Implementation

### Kotlin Side (UI)
The properties are managed as `mutableStateOf` in the Activity. When a property is changed in the UI, an event map is created and sent via `NativeHelper.sendCommands(event)`.

Example:
```kotlin
val event = mapOf("event_id" to "depthtest_event", "on" to it)
NativeHelper.sendCommands(event)
```

### Native Side (GLES)
The native side listens for these event IDs and applies the corresponding OpenGL ES state changes. For selectors, the index provided is usually mapped to the corresponding OpenGL constant.
