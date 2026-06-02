package com.minininja.learngles.lighting

import android.util.Log
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.material3.Checkbox
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
import com.minininja.learngles.GLActivity
import com.minininja.learngles.Layer3DTouchCallback
import com.minininja.learngles.NativeHelper

class PhongVsBlinnActivity : GLActivity() {
    private var active by mutableStateOf(true)

    private var blinnOn by mutableStateOf(true)

    override fun createTouchCallback(): Layer3DTouchCallback {

        return object : Layer3DTouchCallback {
            override fun onSingleTouch(
                prevPoint: Offset,
                point: Offset
            ) {
                if (!active) return
                Log.d("PhongVsBlinnActivity", "onSingleTouch: $prevPoint, $point")
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
                Log.d("PhongVsBlinnActivity", "onDoubleTouch: $prevPoint -> $point, $prevPoint1 -> $point1")
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
                Log.d("PhongVsBlinnActivity", "Custom DoubleClick at: $event")
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
            title = "Blinn On",
            active = blinnOn,
            onActiveChange = {
                blinnOn = it
                val event = mapOf("event_id" to "blinn_on_event", "on" to it)
                glSurfaceView?.queueEvent {
                    NativeHelper.sendCommands(event)
                    glSurfaceView?.requestRender()
                }
            },
        )
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
