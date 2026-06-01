package com.minininja.learngles.ui

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.gestures.detectDragGestures
import androidx.compose.foundation.gestures.detectTapGestures
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.Path
import androidx.compose.ui.graphics.drawscope.Stroke
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.tooling.preview.Preview
import com.minininja.learngles.ui.theme.LearnGLESTheme
import kotlin.math.max
import kotlin.math.min
import kotlin.math.sqrt

// Data class to hold our normalized weights
data class SimplexWeights(val a: Float, val b: Float, val c: Float)

@Composable
fun SimplexTriangleEditor(
    modifier: Modifier = Modifier,
    initialWeights: SimplexWeights = SimplexWeights(0.333f, 0.333f, 0.334f),
    onWeightsChanged: (SimplexWeights) -> Unit
) {
    var weights by remember { mutableStateOf(initialWeights) }

    Box(modifier = modifier) {
        Canvas(
            modifier = Modifier
                .fillMaxSize()
                .pointerInput(Unit) {
                    // Handle dragging the handle
                    detectDragGestures { change, _ ->
                        change.consume()
                        val newWeights = calculateWeightsFromScreenPos(
                            pointerPos = change.position,
                            canvasWidth = size.width.toFloat(),
                            canvasHeight = size.height.toFloat()
                        )
                        weights = newWeights
                        onWeightsChanged(newWeights)
                    }
                }
                .pointerInput(Unit) {
                    // Handle snapping to a direct tap location
                    detectTapGestures { offset ->
                        val newWeights = calculateWeightsFromScreenPos(
                            pointerPos = offset,
                            canvasWidth = size.width.toFloat(),
                            canvasHeight = size.height.toFloat()
                        )
                        weights = newWeights
                        onWeightsChanged(newWeights)
                    }
                }
        ) {
            // 1. Calculate Geometry Layout dynamically based on Canvas boundaries
            val centerX = size.width / 2f
            val centerY = size.height / 2f
            // Use 85% of the shortest dimension as the bounding radius to ensure padding
            val radius = min(size.width, size.height) * 0.425f

            val sqrt3Over2 = sqrt(3f) / 2f

            val vertA = Offset(centerX, centerY - radius)
            val vertB = Offset(centerX - radius * sqrt3Over2, centerY + radius * 0.5f)
            val vertC = Offset(centerX + radius * sqrt3Over2, centerY + radius * 0.5f)

            // 2. Draw the Equilateral Triangle Hull
            val trianglePath = Path().apply {
                moveTo(vertA.x, vertA.y)
                lineTo(vertB.x, vertB.y)
                lineTo(vertC.x, vertC.y)
                close()
            }
            drawPath(path = trianglePath, color = Color.Gray, style = Stroke(width = 4f))

            // Draw distinct corner nodes for visual reference
            drawCircle(color = Color.Red, radius = 12f, center = vertA)   // Vertex A
            drawCircle(color = Color.Green, radius = 12f, center = vertB) // Vertex B
            drawCircle(color = Color.Blue, radius = 12f, center = vertC)  // Vertex C

            // 3. Compute Current 2D Handle Location from Weights (Forward Kinematics)
            val handleX = weights.a * vertA.x + weights.b * vertB.x + weights.c * vertC.x
            val handleY = weights.a * vertA.y + weights.b * vertB.y + weights.c * vertC.y

            // 4. Draw Interactive Selector Handle
            drawCircle(
                color = Color.DarkGray,
                radius = 24f,
                center = Offset(handleX, handleY),
                style = Stroke(width = 6f)
            )
            drawCircle(
                color = Color.White,
                radius = 20f,
                center = Offset(handleX, handleY)
            )
        }
    }
}

// Inverse Kinematics: Maps pixel offsets directly into normalized weights
private fun calculateWeightsFromScreenPos(
    pointerPos: Offset,
    canvasWidth: Float,
    canvasHeight: Float
): SimplexWeights {
    val centerX = canvasWidth / 2f
    val centerY = canvasHeight / 2f
    val radius = min(canvasWidth, canvasHeight) * 0.425f
    val sqrt3Over2 = sqrt(3f) / 2f

    val ax = centerX
    val ay = centerY - radius
    val bx = centerX - radius * sqrt3Over2
    val by = centerY + radius * 0.5f
    val cx = centerX + radius * sqrt3Over2
    val cy = centerY + radius * 0.5f

    // Determinant of the barycentric transformation matrix
    val delta = (by - cy) * (ax - cx) + (cx - bx) * (ay - cy)

    // Compute raw weights using area cross products
    var rawA = ((by - cy) * (pointerPos.x - cx) + (cx - bx) * (pointerPos.y - cy)) / delta
    var rawB = ((cy - ay) * (pointerPos.x - cx) + (ax - cx) * (pointerPos.y - cy)) / delta

    // Clamp values inside [0.0, 1.0] boundaries
    rawA = max(0f, min(1f, rawA))
    rawB = max(0f, min(1f, rawB))
    var rawC = max(0f, min(1f, 1f - rawA - rawB))

    // Re-normalize weight vectors to eliminate tracking precision loss outside bounds
    val sum = rawA + rawB + rawC
    return if (sum > 0f) {
        SimplexWeights(rawA / sum, rawB / sum, rawC / sum)
    } else {
        SimplexWeights(0.333f, 0.333f, 0.334f)
    }
}

@Preview(showBackground = true)
@Composable
fun SimplexTriangleEditorPreview() {
    LearnGLESTheme {
        SimplexTriangleEditor(
            modifier = Modifier.fillMaxSize(),
            initialWeights = SimplexWeights(0.333f, 0.333f, 0.334f),
            onWeightsChanged = {}
        )
    }
}
