package com.minininja.learngles.ui

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.layout.aspectRatio
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.Path
import androidx.compose.ui.graphics.drawscope.Stroke
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp

@Composable
fun LearnGLESLogo(modifier: Modifier = Modifier) {
    Canvas(
        modifier = modifier
            .aspectRatio(1f)
            .padding(16.dp)
    ) {
        val width = size.width
        val height = size.height
        
        // Define points based on the vector coordinates (normalized to size)
        val center = Offset(width * 0.5f, height * 0.5f)
        val top = Offset(width * 0.5f, height * 0.23f)
        val bottom = Offset(width * 0.5f, height * 0.78f)
        val left = Offset(width * 0.22f, height * 0.37f)
        val right = Offset(width * 0.78f, height * 0.37f)
        val bottomLeft = Offset(width * 0.22f, height * 0.65f)
        val bottomRight = Offset(width * 0.78f, height * 0.65f)
        val innerCenter = Offset(width * 0.5f, height * 0.51f)

        // Right Face (Blue)
        val rightFace = Path().apply {
            moveTo(top.x, top.y)
            lineTo(right.x, right.y)
            lineTo(bottomRight.x, bottomRight.y)
            lineTo(bottom.x, bottom.y)
            close()
        }
        drawPath(
            path = rightFace,
            brush = Brush.linearGradient(
                colors = listOf(Color(0xFF007FFF), Color(0xFF003366)),
                start = top,
                end = bottomRight
            ),
            alpha = 0.8f
        )

        // Left Face (Green)
        val leftFace = Path().apply {
            moveTo(top.x, top.y)
            lineTo(left.x, left.y)
            lineTo(bottomLeft.x, bottomLeft.y)
            lineTo(bottom.x, bottom.y)
            close()
        }
        drawPath(
            path = leftFace,
            brush = Brush.linearGradient(
                colors = listOf(Color(0xFF00FF7F), Color(0xFF006633)),
                start = top,
                end = bottomLeft
            ),
            alpha = 0.9f
        )

        // Top Face (Red)
        val topFace = Path().apply {
            moveTo(top.x, top.y)
            lineTo(right.x, right.y)
            lineTo(innerCenter.x, innerCenter.y)
            lineTo(left.x, left.y)
            close()
        }
        drawPath(
            path = topFace,
            brush = Brush.linearGradient(
                colors = listOf(Color(0xFFFF4D4D), Color(0xFF990000)),
                start = top,
                end = innerCenter
            )
        )

        // Wireframe Highlights
        drawLine(
            color = Color.White.copy(alpha = 0.3f),
            start = top,
            end = innerCenter,
            strokeWidth = 2f
        )
        drawLine(
            color = Color.White.copy(alpha = 0.3f),
            start = innerCenter,
            end = left,
            strokeWidth = 2f
        )
        drawLine(
            color = Color.White.copy(alpha = 0.3f),
            start = innerCenter,
            end = right,
            strokeWidth = 2f
        )
    }
}

@Preview(showBackground = true, backgroundColor = 0xFF1A1A1A)
@Composable
fun PreviewLogo() {
    LearnGLESLogo(Modifier.padding(50.dp))
}
