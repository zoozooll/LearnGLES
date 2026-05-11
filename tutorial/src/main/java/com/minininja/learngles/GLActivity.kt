package com.minininja.learngles

import android.opengl.GLES30
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.gestures.detectTapGestures
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.viewinterop.AndroidView
import com.minininja.learngles.ui.theme.LearnGLESTheme
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import kotlin.math.atan2

open class GLActivity : ComponentActivity() {
    protected var glSurfaceView: GLSurfaceView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        NativeHelper.setupNativeAsset(assets)
        NativeHelper.setupInternalPath(getExternalFilesDir("files")?.path)
        setContent {
            LearnGLESTheme {
                OpenGLContainer(
                    renderer = createRenderer(),
                    touchCallback = createTouchCallback(),
                    onViewCreated = { glSurfaceView = it }
                )
            }
        }
    }

    open fun createRenderer(): GLSurfaceView.Renderer {
        return object : GLSurfaceView.Renderer {
            override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
                NativeHelper.nativeOnInit(intent.getStringExtra("tutorial_key"))
            }

            override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
                NativeHelper.nativeSizeChanged(width, height)
            }

            override fun onDrawFrame(gl: GL10?) {
                NativeHelper.nativeDraw()
            }
        }
    }

    open fun createTouchCallback(): Layer3DTouchCallback {
        return object : Layer3DTouchCallback {
            override fun onSingleTouch(disX: Float, disY: Float) {
                Log.i("GLActivity", "onSingleTouch disX: $disX, disY: $disY")
                glSurfaceView?.requestRender()
            }

            override fun onZooming(prevDistance: Float, distance: Float) {
                Log.i("GLActivity", "onZooming prevDistance: $prevDistance, distance: $distance")
                glSurfaceView?.requestRender()
            }

            override fun onTwoFingersRotating(angle: Float) {
                Log.i("GLActivity", "onTwoFingersRotating angle: $angle")
                glSurfaceView?.requestRender()
            }

            override fun onMoving(prevCenter: Offset, centerPoint: Offset) {
                Log.i("GLActivity", "onMoving prevCenter: $prevCenter, centerPoint: $centerPoint")
                glSurfaceView?.requestRender()
            }

            override fun onLongPress(event: Offset) {
                Log.i("GLActivity", "onLongPress event: $event")
            }

            override fun onSingleClick(event: Offset) {
                Log.i("GLActivity", "onSingleClick event: $event")
            }

            override fun onDoubleClick(event: Offset) {
                Log.i("GLActivity", "onDoubleClick event: $event")
            }

            override fun onActionUp(event: Offset) {
                Log.i("GLActivity", "onActionUp event: $event")
            }

            override fun onTwoFingersClick() {
                Log.i("GLActivity", "onTwoFingersClick")
            }

            override fun onThreeFingersClick() {
                Log.i("GLActivity", "onThreeFingersClick")
            }
        }
    }
}



fun Modifier.layer3DTouch(callback: Layer3DTouchCallback): Modifier = this
    // Block 1: Standard Gestures (Single/Double Tap, Long Press)
    .pointerInput(Unit) {
        detectTapGestures(
            onTap = { callback.onSingleClick(it) },
            onDoubleTap = { callback.onDoubleClick(it) },
            onLongPress = { callback.onLongPress(it) }
        )
    }
    // Block 2: Custom Math & Multi-finger Taps
    .pointerInput(Unit) {
        awaitPointerEventScope {
            var maxPointers = 0
            var touchStartTime = 0L

            while (true) {
                val event = awaitPointerEvent()
                val changes = event.changes
                val pressedChanges = changes.filter { it.pressed }
                val currentPointerCount = pressedChanges.size

                // --- MULTI-FINGER TAP DETECTION ---
                // Replaces the complex Handler/Timeout logic
                if (currentPointerCount > 0 && maxPointers == 0) {
                    touchStartTime = System.currentTimeMillis()
                }

                if (currentPointerCount > maxPointers) {
                    maxPointers = currentPointerCount
                }

                if (currentPointerCount == 0 && maxPointers > 0) {
                    val duration = System.currentTimeMillis() - touchStartTime

                    // If all fingers lifted within 300ms, register as a click
                    if (duration < 300L) {
                        if (maxPointers == 2) callback.onTwoFingersClick()
                        if (maxPointers == 3) callback.onThreeFingersClick()
                    }

                    val lastReleased = changes.firstOrNull()?.position ?: Offset.Zero
                    callback.onActionUp(lastReleased)

                    // Reset for next touch
                    maxPointers = 0
                }

                // --- DRAG & TRANSFORMATIONS ---
                if (currentPointerCount == 1) {
                    val change = pressedChanges[0]
                    val current = change.position
                    val prev = change.previousPosition

                    if (current != prev) {
                        // Preserved your exact logic: end.x - start.x, start.y - end.y
                        callback.onSingleTouch(current.x - prev.x, prev.y - current.y)
                    }

                } else if (currentPointerCount == 2) {
                    val p0 = pressedChanges[0].position
                    val p1 = pressedChanges[1].position
                    val p0Prev = pressedChanges[0].previousPosition
                    val p1Prev = pressedChanges[1].previousPosition

                    // 1. Distance (Zooming)
                    val distance = (p0 - p1).getDistance()
                    val prevDistance = (p0Prev - p1Prev).getDistance()

                    // 2. Center (Moving/Panning)
                    val center = (p0 + p1) / 2f
                    val prevCenter = (p0Prev + p1Prev) / 2f

                    // 3. Angle (Rotating) - Preserved exact atan2 math
                    val vec0 = p1Prev - p0Prev
                    val vec1 = p1 - p0
                    val rsA = vec1.y * vec0.x - vec1.x * vec0.y
                    val rsB = vec0.x * vec1.x + vec0.y * vec1.y
                    val angle = -atan2(rsA, rsB)

                    // Fire callbacks
                    callback.onZooming(prevDistance, distance)
                    callback.onTwoFingersRotating(angle)
                    callback.onMoving(prevCenter, center)
                }
            }
        }
    }

@Composable
fun OpenGLContainer(
    renderer: GLSurfaceView.Renderer,
    touchCallback: Layer3DTouchCallback,
    onViewCreated: (GLSurfaceView) -> Unit = {}
) {
    Box(
        modifier = Modifier
            .fillMaxSize()
            .layer3DTouch(touchCallback) // Apply the callback here
    ) {
        AndroidView(
            factory = { context ->
                GLSurfaceView(context).apply {
                    setEGLContextClientVersion(3)
                    setRenderer(renderer)
                    renderMode = GLSurfaceView.RENDERMODE_WHEN_DIRTY
                    onViewCreated(this)
                }
            },
            modifier = Modifier.fillMaxSize()
        )
    }
}


@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    LearnGLESTheme {
        val dummyRenderer = object : GLSurfaceView.Renderer {
            override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {}
            override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {}
            override fun onDrawFrame(gl: GL10?) {}
        }
        val dummyCallback = object : Layer3DTouchCallback {
            override fun onSingleTouch(disX: Float, disY: Float) {}
            override fun onZooming(prevDistance: Float, distance: Float) {}
            override fun onTwoFingersRotating(angle: Float) {}
            override fun onMoving(prevCenter: Offset, centerPoint: Offset) {}
            override fun onLongPress(event: Offset) {}
            override fun onSingleClick(event: Offset) {}
            override fun onDoubleClick(event: Offset) {}
            override fun onActionUp(event: Offset) {}
            override fun onTwoFingersClick() {}
            override fun onThreeFingersClick() {}
        }
        OpenGLContainer(renderer = dummyRenderer, touchCallback = dummyCallback)
    }
}

interface Layer3DTouchCallback {
    fun onSingleTouch(disX: Float, disY: Float)
    fun onZooming(prevDistance: Float, distance: Float)
    fun onTwoFingersRotating(angle: Float)
    fun onMoving(prevCenter: Offset, centerPoint: Offset)
    fun onLongPress(event: Offset)
    fun onSingleClick(event: Offset)
    fun onDoubleClick(event: Offset)
    fun onActionUp(event: Offset)
    fun onTwoFingersClick()
    fun onThreeFingersClick()
}
