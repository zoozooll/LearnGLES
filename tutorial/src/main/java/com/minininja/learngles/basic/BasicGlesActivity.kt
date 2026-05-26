package com.minininja.learngles.basic

import android.opengl.GLSurfaceView
import android.util.Log
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Checkbox
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.unit.dp
import androidx.compose.ui.tooling.preview.Preview
import com.minininja.learngles.ui.theme.LearnGLESTheme
import com.minininja.learngles.GLActivity
import com.minininja.learngles.Layer3DTouchCallback
import com.minininja.learngles.NativeHelper
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class BasicGlesActivity : GLActivity() {
    private var active by mutableStateOf(true)

    override fun createTouchCallback(): Layer3DTouchCallback {

        return object : Layer3DTouchCallback {
            override fun onSingleTouch(disX: Float, disY: Float) {
                if (!active) return
                Log.d("BasicGlesActivity", "Custom SingleTouch: $disX, $disY")
                val event = mapOf("event_id" to "target_camera_touching_event",
                    "single_touching" to floatArrayOf(disX, disY))
                NativeHelper.sendCommands(event)
                glSurfaceView?.requestRender()
            }

            override fun onZooming(prevDistance: Float, distance: Float) {
                if (!active) return
                Log.d("BasicGlesActivity", "Custom Zooming: $distance")
                val event = mapOf("event_id" to "target_camera_touching_event",
                    "zooming" to floatArrayOf(prevDistance, distance))
                NativeHelper.sendCommands(event)
                glSurfaceView?.requestRender()
            }

            override fun onTwoFingersRotating(angle: Float) {
                if (!active) return
                Log.d("BasicGlesActivity", "Custom Rotating: $angle")
                val event = mapOf("event_id" to "target_camera_touching_event",
                    "rotating" to angle)
                NativeHelper.sendCommands(event)
                glSurfaceView?.requestRender()
            }

            override fun onMoving(prevCenter: Offset, centerPoint: Offset) {
                if (!active) return
                Log.d("BasicGlesActivity", "Custom Moving: $centerPoint")
                val event = mapOf("event_id" to "target_camera_touching_event",
                    "moving" to centerPoint - prevCenter)
                NativeHelper.sendCommands(event)
                glSurfaceView?.requestRender()
            }

            override fun onLongPress(event: Offset) {
                if (!active) return
                Log.d("BasicGlesActivity", "Custom LongPress at: $event")
            }

            override fun onSingleClick(event: Offset) {
                if (!active) return
                Log.d("BasicGlesActivity", "Custom SingleClick at: $event")
            }

            override fun onDoubleClick(event: Offset) {
                if (!active) return
                val event = mapOf("event_id" to "target_camera_touching_event",
                    "reset" to 1)
                NativeHelper.sendCommands(event)
                Log.d("BasicGlesActivity", "Custom DoubleClick at: $event")
            }

            override fun onActionUp(event: Offset) {
                if (!active) return
                Log.d("BasicGlesActivity", "Custom ActionUp")
            }

            override fun onTwoFingersClick() {
                if (!active) return
                Log.d("BasicGlesActivity", "Custom TwoFingersClick")
            }

            override fun onThreeFingersClick() {
                if (!active) return
                Log.d("BasicGlesActivity", "Custom ThreeFingersClick")
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

@Preview(showBackground = true)
@Composable
private fun ControlPanelPreview() {
    LearnGLESTheme {
        ControlPanelContent(
            active = true,
            onActiveChange = {}
        )
    }
}
