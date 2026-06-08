package com.minininja.learngles.lighting

import android.util.Log
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.material3.Checkbox
import androidx.compose.material3.Slider
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import androidx.compose.ui.tooling.preview.Preview
import com.minininja.learngles.GLActivity
import com.minininja.learngles.Layer3DTouchCallback
import com.minininja.learngles.NativeHelper
import com.minininja.learngles.ui.theme.LearnGLESTheme

class LightCasterActivity : GLActivity() {
    private var active by mutableStateOf(true)

    private var ambientFactor by mutableStateOf(0.35f)
    private var diffuseFactor by mutableStateOf(0.5f)
    private var specularFactor by mutableStateOf(1.0f)

    override fun createTouchCallback(): Layer3DTouchCallback {

        return object : Layer3DTouchCallback {
            override fun onSingleTouch(
                prevPoint: Offset,
                point: Offset
            ) {
                if (!active) return
                Log.d("LightCasterActivity", "onSingleTouch: $prevPoint, $point")
                val event = mapOf("event_id" to "target_camera_touching_event",
                    "single_touching" to floatArrayOf(prevPoint.x, prevPoint.y, point.x, point.y))
                NativeHelper.sendCommands(event)
                glSurfaceView?.requestRender()
            }

            override fun onDoubleTouch(
                prevPoint: Offset,
                point: Offset,
                prevPoint1: Offset,
                point1: Offset
            ) {
                if (!active) return
                Log.d("LightCasterActivity", "onDoubleTouch: $prevPoint -> $point, $prevPoint1 -> $point1")
                val event = mapOf("event_id" to "target_camera_touching_event",
                    "double_touching" to floatArrayOf(prevPoint.x, prevPoint.y, point.x, point.y,
                        prevPoint1.x, prevPoint1.y, point1.x, point1.y))
                NativeHelper.sendCommands(event)
                glSurfaceView?.requestRender()
            }

            override fun onLongPress(event: Offset) {
            }

            override fun onSingleClick(event: Offset) {
            }

            override fun onDoubleClick(event: Offset) {
                if (!active) return
                val event = mapOf("event_id" to "target_camera_touching_event",
                    "reset" to 1)
                NativeHelper.sendCommands(event)
                Log.d("LightCasterActivity", "Custom DoubleClick at: $event")
                glSurfaceView?.requestRender()
            }

            override fun onActionUp(event: Offset) {
            }

            override fun onTwoFingersClick() {
            }

            override fun onThreeFingersClick() {
            }
        }
    }

    @Composable
    override fun ControlPanel() {
        ControlPanelContent(
            active = active,
            onActiveChange = {
                active = it
            },
            ambientFactor = ambientFactor,
            onAmbientFactorChange = {
                ambientFactor = it
                updateProperty("ambientFactor", it)
            },
            diffuseFactor = diffuseFactor,
            onDiffuseFactorChange = {
                diffuseFactor = it
                updateProperty("diffuseFactor", it)
            },
            specularFactor = specularFactor,
            onSpecularFactorChange = {
                specularFactor = it
                updateProperty("specularFactor", it)
            }
        )
    }

    private fun updateProperty(name: String, value: Float) {
        val event = mapOf(name to value)
        NativeHelper.sendCommands(event)
        glSurfaceView?.requestRender()
    }
}

@Composable
private fun ControlPanelContent(
    active: Boolean,
    onActiveChange: (Boolean) -> Unit,
    ambientFactor: Float,
    onAmbientFactorChange: (Float) -> Unit,
    diffuseFactor: Float,
    onDiffuseFactorChange: (Float) -> Unit,
    specularFactor: Float,
    onSpecularFactorChange: (Float) -> Unit,
    modifier: Modifier = Modifier,
) {
    Column(
        modifier = modifier.wrapContentSize().padding(8.dp)
    ) {
        Row(verticalAlignment = Alignment.CenterVertically) {
            Text(text = "Target Camera Events", color = Color.White)
            Checkbox(
                checked = active,
                onCheckedChange = onActiveChange
            )
        }

        FactorSlider(label = "Ambient Factor", value = ambientFactor, onValueChange = onAmbientFactorChange)
        FactorSlider(label = "Diffuse Factor", value = diffuseFactor, onValueChange = onDiffuseFactorChange)
        FactorSlider(label = "Specular Factor", value = specularFactor, onValueChange = onSpecularFactorChange)
    }
}

@Composable
private fun FactorSlider(
    label: String,
    value: Float,
    onValueChange: (Float) -> Unit,
    modifier: Modifier = Modifier
) {
    Column(modifier = modifier.padding(vertical = 4.dp)) {
        Text(text = "$label: ${"%.2f".format(value)}", color = Color.White)
        Slider(
            value = value,
            onValueChange = onValueChange,
            valueRange = 0f..1f
        )
    }
}

@Preview(showBackground = true, backgroundColor = 0xFF000000)
@Composable
private fun ControlPanelPreview() {
    LearnGLESTheme {
        ControlPanelContent(
            active = true,
            onActiveChange = {},
            ambientFactor = 0.35f,
            onAmbientFactorChange = {},
            diffuseFactor = 0.5f,
            onDiffuseFactorChange = {},
            specularFactor = 1.0f,
            onSpecularFactorChange = {}
        )
    }
}
