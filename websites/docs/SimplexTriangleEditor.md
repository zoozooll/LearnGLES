# SimplexTriangleEditor

The `SimplexTriangleEditor` is a Jetpack Compose UI component that provides an interactive equilateral triangle for selecting barycentric weights. It is particularly useful for blending three different properties, such as colors, textures, or shader parameters.

## Features

- **Visual Interaction**: Drag or tap anywhere inside the triangle to move the selector handle.
- **Barycentric Mapping**: Automatically calculates three normalized weights ($a + b + c = 1.0$) based on the handle's position.
- **Responsive Layout**: Dynamically adjusts its geometry based on the available canvas size.
- **Visual Cues**: Colors the vertices (Red, Green, Blue) to represent the weight influence of each corner.

## Usage

### Data Model

The widget uses a simple data class to hold the weights:

```kotlin
data class SimplexWeights(val a: Float, val b: Float, val c: Float)
```

### Basic Example

```kotlin
@Composable
fun WeightSelectionScreen() {
    var weights by remember { 
        mutableStateOf(SimplexWeights(0.333f, 0.333f, 0.334f)) 
    }

    SimplexTriangleEditor(
        modifier = Modifier.size(300.dp),
        initialWeights = weights,
        onWeightsChanged = { newWeights ->
            weights = newWeights
            // Update your logic or native shaders here
            println("Weights: A=${newWeights.a}, B=${newWeights.b}, C=${newWeights.c}")
        }
    )
}
```

## Parameters

| Parameter | Type | Description |
| :--- | :--- | :--- |
| `modifier` | `Modifier` | Standard Compose modifier for layout and sizing. |
| `initialWeights` | `SimplexWeights` | The starting position of the selector handle. Defaults to center. |
| `onWeightsChanged` | `(SimplexWeights) -> Unit` | Callback triggered whenever the handle is moved or tapped. |

## Implementation Details

The widget implements **Inverse Kinematics** to map 2D pixel offsets from the screen into normalized barycentric coordinates. It ensures that even if a user taps slightly outside the triangle bounds, the resulting weights are clamped and re-normalized to maintain a valid state for rendering engines.

---

*Part of the LearnGLES tutorial series.*
