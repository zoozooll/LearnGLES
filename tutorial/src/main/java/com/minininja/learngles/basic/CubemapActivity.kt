package com.minininja.learngles.basic

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

class CubemapActivity : GLActivity() {
    private var active by mutableStateOf(true)

    override fun createTouchCallback(): Layer3DTouchCallback {

        return object : Layer3DTouchCallback {
            override fun onSingleTouch(
                prevPoint: Offset,
                point: Offset
            ) {
                if (!active) return
                Log.d("CubemapActivity", "onSingleTouch: $prevPoint, $point")
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
                Log.d("CubemapActivity", "onDoubleTouch: $prevPoint -> $point, $prevPoint1 -> $point1")
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
                Log.d("CubemapActivity", "Custom DoubleClick at: $event")
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
        )
    }
}

@Composable
private fun ControlPanelContent(
    active: Boolean,
    onActiveChange: (Boolean) -> Unit,
    modifier: Modifier = Modifier,
) {
    Column(
        modifier = modifier.wrapContentSize()
    ) {
        Row(verticalAlignment = Alignment.CenterVertically,
            modifier = modifier.padding(8.dp)) {
            Text(text = "Target Camera Events", color = Color.White)
            Checkbox(
                checked = active,
                onCheckedChange = onActiveChange
            )
        }
    }
}
