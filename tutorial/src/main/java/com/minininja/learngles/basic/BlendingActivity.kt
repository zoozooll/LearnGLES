package com.minininja.learngles.basic

import android.util.Log
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.foundation.layout.width
import androidx.compose.material3.Checkbox
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.ExposedDropdownMenuBox
import androidx.compose.material3.ExposedDropdownMenuDefaults
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import com.minininja.learngles.GLActivity
import com.minininja.learngles.Layer3DTouchCallback
import com.minininja.learngles.NativeHelper

class BlendingActivity : GLActivity() {
    private var active by mutableStateOf(true)

    private var blendOn by mutableStateOf(true)

    private var srcFactorIndex by mutableStateOf(6) // GL_SRC_ALPHA

    private var dstFactorIndex by mutableStateOf(7) // GL_ONE_MINUS_SRC_ALPHA

    private var blendEquationIndex by mutableStateOf(0) // GL_FUNC_ADD

    private val blendingFactors = listOf(
        "GL_ZERO", "GL_ONE", "GL_SRC_COLOR", "GL_ONE_MINUS_SRC_COLOR",
        "GL_DST_COLOR", "GL_ONE_MINUS_DST_COLOR", "GL_SRC_ALPHA", "GL_ONE_MINUS_SRC_ALPHA",
        "GL_DST_ALPHA", "GL_ONE_MINUS_DST_ALPHA", "GL_CONSTANT_COLOR", "GL_ONE_MINUS_CONSTANT_COLOR",
        "GL_CONSTANT_ALPHA", "GL_ONE_MINUS_CONSTANT_ALPHA"
    )

    private val blendingEquations = listOf(
        "GL_FUNC_ADD", "GL_FUNC_SUBTRACT", "GL_FUNC_REVERSE_SUBTRACT", "GL_MIN", "GL_MAX"
    )

    override fun createTouchCallback(): Layer3DTouchCallback {

        return object : Layer3DTouchCallback {
            override fun onSingleTouch(
                prevPoint: Offset,
                point: Offset
            ) {
                if (!active) return
                Log.d("BlendingActivity", "onSingleTouch: $prevPoint, $point")
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
                Log.d("BlendingActivity", "onDoubleTouch: $prevPoint -> $point, $prevPoint1 -> $point1")
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
                glSurfaceView?.requestRender()
                Log.d("BlendingActivity", "Custom DoubleClick at: $event")
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
            title = "Target Camera Events",
            active = active,
            onActiveChange = {
                active = it
            },
        )

        ControlPanelContent(
            title = "Blend On",
            active = blendOn,
            onActiveChange = {
                blendOn = it
                val event = mapOf("event_id" to "blend_on_event", "on" to it)
                glSurfaceView?.queueEvent {
                    NativeHelper.sendCommands(event)
                    glSurfaceView?.requestRender()
                }
            },
        )

        SelectorControlPanelContent(
            title = "Source Factor",
            options = blendingFactors,
            selectedIndex = srcFactorIndex,
            onOptionSelected = { index ->
                srcFactorIndex = index
                val event = mapOf("event_id" to "src_factor_event", "factor" to index)
                glSurfaceView?.queueEvent {
                    NativeHelper.sendCommands(event)
                    glSurfaceView?.requestRender()
                }
            }
        )

        SelectorControlPanelContent(
            title = "Destination Factor",
            options = blendingFactors,
            selectedIndex = dstFactorIndex,
            onOptionSelected = { index ->
                dstFactorIndex = index
                val event = mapOf("event_id" to "dst_factor_event", "factor" to index)
                glSurfaceView?.queueEvent {
                    NativeHelper.sendCommands(event)
                    glSurfaceView?.requestRender()
                }
            }
        )

        SelectorControlPanelContent(
            title = "Blend Equation",
            options = blendingEquations,
            selectedIndex = blendEquationIndex,
            onOptionSelected = { index ->
                blendEquationIndex = index
                val event = mapOf("event_id" to "blend_equation_event", "mode" to index)
                glSurfaceView?.queueEvent {
                    NativeHelper.sendCommands(event)
                    glSurfaceView?.requestRender()
                }
            }
        )
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
private fun SelectorControlPanelContent(
    title: String,
    options: List<String>,
    selectedIndex: Int,
    onOptionSelected: (Int) -> Unit,
    modifier: Modifier = Modifier,
) {
    var expanded by remember { mutableStateOf(false) }

    Column(
        modifier = modifier
            .padding(8.dp)
            .wrapContentSize()
    ) {
        Text(text = title, color = Color.White, modifier = Modifier.padding(bottom = 4.dp))
        ExposedDropdownMenuBox(
            expanded = expanded,
            onExpandedChange = { expanded = !expanded },
            modifier = Modifier.width(200.dp)
        ) {
            TextField(
                value = options[selectedIndex],
                onValueChange = {},
                readOnly = true,
                trailingIcon = { ExposedDropdownMenuDefaults.TrailingIcon(expanded = expanded) },
                colors = ExposedDropdownMenuDefaults.textFieldColors(),
                modifier = Modifier.menuAnchor()
            )
            ExposedDropdownMenu(
                expanded = expanded,
                onDismissRequest = { expanded = false }
            ) {
                options.forEachIndexed { index, selectionOption ->
                    DropdownMenuItem(
                        text = { Text(text = selectionOption) },
                        onClick = {
                            onOptionSelected(index)
                            expanded = false
                        }
                    )
                }
            }
        }
    }
}

@Composable
private fun ControlPanelContent(
    title: String,
    active: Boolean,
    onActiveChange: (Boolean) -> Unit,
    modifier: Modifier = Modifier,
) {
    Column(
        modifier = modifier.wrapContentSize()
    ) {
        Row(verticalAlignment = Alignment.CenterVertically,
            modifier = modifier.padding(8.dp)) {
            Text(text = title, color = Color.White)
            Checkbox(
                checked = active,
                onCheckedChange = onActiveChange
            )
        }
    }
}
