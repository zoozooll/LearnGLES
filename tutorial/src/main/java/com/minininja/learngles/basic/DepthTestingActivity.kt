package com.minininja.learngles.basic

import android.util.Log
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.material3.Checkbox
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.ExposedDropdownMenuBox
import androidx.compose.material3.ExposedDropdownMenuDefaults
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.remember
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
import com.minininja.learngles.ui.theme.LearnGLESTheme
import com.minininja.learngles.GLActivity
import com.minininja.learngles.Layer3DTouchCallback
import com.minininja.learngles.NativeHelper

class DepthTestingActivity : GLActivity() {
    private var active by mutableStateOf(true)

    private var cullFaceOn by mutableStateOf(true)

    private var depthTestOn by mutableStateOf(true)

    private var showDepthOn by mutableStateOf(false)

    private var depthFuncIndex by mutableStateOf(1) // Default to GL_LESS (index 1)

    private val depthFuncs = listOf(
        "GL_NEVER", "GL_LESS", "GL_EQUAL", "GL_LEQUAL",
        "GL_GREATER", "GL_NOTEQUAL", "GL_GEQUAL", "GL_ALWAYS"
    )

    override fun createTouchCallback(): Layer3DTouchCallback {

        return object : Layer3DTouchCallback {
            override fun onSingleTouch(
                prevPoint: Offset,
                point: Offset
            ) {
                if (!active) return
                Log.d("DepthTestingActivity", "onSingleTouch: $prevPoint, $point")
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
                Log.d("DepthTestingActivity", "onDoubleTouch: $prevPoint -> $point, $prevPoint1 -> $point1")
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
                Log.d("DepthTestingActivity", "Custom DoubleClick at: $event")
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
            title = "Target Camera Events",
            active = active,
            onActiveChange = {
                active = it
            },
        )

        ControlPanelContent(
            title = "Cull Face",
            active = cullFaceOn,
            onActiveChange = {
                cullFaceOn = it
                val event = mapOf("event_id" to "cullface_event", "on" to it)
                glSurfaceView?.queueEvent {
                    NativeHelper.sendCommands(event)
                    glSurfaceView?.requestRender()
                }
            },
        )

        ControlPanelContent(
            title = "Depth Test",
            active = depthTestOn,
            onActiveChange = {
                depthTestOn = it
                val event = mapOf("event_id" to "depthtest_event", "on" to it)
                glSurfaceView?.queueEvent {
                    NativeHelper.sendCommands(event)
                    glSurfaceView?.requestRender()
                }
            },
        )

        ControlPanelContent(
            title = "Show Depth",
            active = showDepthOn,
            onActiveChange = {
                showDepthOn = it
                val event = mapOf("event_id" to "show_depth_event", "on" to it)
                glSurfaceView?.queueEvent {
                    NativeHelper.sendCommands(event)
                    glSurfaceView?.requestRender()
                }
            },
        )

        SelectorControlPanelContent(
            title = "Depth Func",
            options = depthFuncs,
            selectedIndex = depthFuncIndex,
            onOptionSelected = { index ->
                depthFuncIndex = index
                val event = mapOf("event_id" to "depthtest_func_event", "func" to index)
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

@Preview(showBackground = true)
@Composable
private fun ControlPanelPreview() {
    LearnGLESTheme {
        ControlPanelContent(
            title = "Target Camera Events",
            active = true,
            onActiveChange = {}
        )
    }
}
