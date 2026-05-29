package com.minininja.learngles

import android.opengl.GLSurfaceView
import android.opengl.GLSurfaceView.EGLContextFactory
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.animation.AnimatedVisibility
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.gestures.detectTapGestures
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.IntrinsicSize
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.displayCutoutPadding
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Close
import androidx.compose.material.icons.filled.Settings
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.viewinterop.AndroidView
import com.minininja.learngles.ui.theme.LearnGLESTheme
import javax.microedition.khronos.egl.EGL10
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.egl.EGLContext
import javax.microedition.khronos.egl.EGLDisplay
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
                    onViewCreated = { glSurfaceView = it },
                    overlay = { ControlPanel() }
                )
            }
        }
    }

    @Composable
    open fun ControlPanel() {
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

    open fun createTouchCallback(): Layer3DTouchCallback? {
        return null
    }
}

fun Modifier.layer3DTouch(callback: Layer3DTouchCallback?): Modifier = this
    // Block 1: Standard Gestures (Single/Double Tap, Long Press)
    .pointerInput(Unit) {
        callback?.let { callback->
            detectTapGestures(
                onTap = { callback.onSingleClick(it) },
                onDoubleTap = { callback.onDoubleClick(it) },
                onLongPress = { callback.onLongPress(it) }
            )
        }
    }
    // Block 2: Custom Math & Multi-finger Taps
    .pointerInput(Unit) {
        callback?.let { callback->
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
                            callback.onSingleTouch(prev, current)
                        }

                    } else if (currentPointerCount == 2) {
                        val p0 = pressedChanges[0].position
                        val p1 = pressedChanges[1].position
                        val p0Prev = pressedChanges[0].previousPosition
                        val p1Prev = pressedChanges[1].previousPosition

                        // Fire callbacks
                        callback.onDoubleTouch(p0Prev, p0, p1Prev, p1)
                    }
                }
            }
        }
    }

@Composable
fun OpenGLContainer(
    renderer: GLSurfaceView.Renderer,
    touchCallback: Layer3DTouchCallback?,
    onViewCreated: (GLSurfaceView) -> Unit = {},
    overlay: @Composable () -> Unit = {}
) {
    var isExpanded by remember { mutableStateOf(true) }

    Box(
        modifier = Modifier
            .fillMaxSize()
            .layer3DTouch(touchCallback) // Apply the callback here
    ) {
        AndroidView(
            factory = { context ->
                GLSurfaceView(context).apply {
                    setEGLContextClientVersion(3)
                    setEGLContextFactory(object : EGLContextFactory {
                        private val EGL_CONTEXT_CLIENT_VERSION = 0x3098

                        public override fun createContext(
                            egl: EGL10,
                            display: EGLDisplay?,
                            eglConfig: EGLConfig?
                        ): EGLContext? {
                            val attrib_list =
                                intArrayOf(EGL_CONTEXT_CLIENT_VERSION, 3, EGL10.EGL_NONE)
                            return egl.eglCreateContext(
                                display,
                                eglConfig,
                                EGL10.EGL_NO_CONTEXT,
                                attrib_list
                            )
                        }

                        public override fun destroyContext(
                            egl: EGL10,
                            display: EGLDisplay?,
                            context: EGLContext?
                        ) {
                            // 1. This runs on the GL Thread!
                            // 2. The context is still alive here!
                            NativeHelper.nativeDestroy()
                             // 3. Let EGL destroy the context now that you are done
                            egl.eglDestroyContext(display, context)
                        }
                    })
                    setRenderer(renderer)
                    renderMode = GLSurfaceView.RENDERMODE_WHEN_DIRTY
                    onViewCreated(this)
                }
            },
            modifier = Modifier.fillMaxSize()
        )
        Box(
            modifier = Modifier
                .displayCutoutPadding()
                .padding(top = 8.dp, start = 8.dp)
                .background(Color.Black.copy(alpha = 0.3f), RoundedCornerShape(8.dp))
                .padding(if (isExpanded) 4.dp else 8.dp)
                .wrapContentSize()
        ) {
            Column(modifier = Modifier.width(IntrinsicSize.Max)) {
                if (!isExpanded) {
                    Icon(
                        imageVector = Icons.Default.Settings,
                        contentDescription = "Expand",
                        tint = Color.White,
                        modifier = Modifier
                            .size(24.dp)
                            .clickable { isExpanded = true }
                    )
                }
                AnimatedVisibility(visible = isExpanded) {
                    Column {
                        Row(
                            modifier = Modifier
                                .fillMaxWidth()
                                .clickable { isExpanded = false },
                            horizontalArrangement = Arrangement.End,
                            verticalAlignment = Alignment.CenterVertically
                        ) {
                            Icon(
                                imageVector = Icons.Default.Close,
                                contentDescription = "Collapse",
                                tint = Color.White,
                                modifier = Modifier
                                    .padding(4.dp)
                                    .size(16.dp)
                            )
                        }
                        overlay()
                    }
                }
            }
        }
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
        val dummyCallback = null
        OpenGLContainer(renderer = dummyRenderer, touchCallback = dummyCallback)
    }
}

interface Layer3DTouchCallback {
    fun onSingleTouch(prevPoint: Offset, point: Offset)
    fun onDoubleTouch(prevPoint: Offset, point: Offset, prevPoint1: Offset, point1: Offset)
    fun onLongPress(event: Offset)
    fun onSingleClick(event: Offset)
    fun onDoubleClick(event: Offset)
    fun onActionUp(event: Offset)
    fun onTwoFingersClick()
    fun onThreeFingersClick()
}
