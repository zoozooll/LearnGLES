package com.minininja.learngles.basic

import android.opengl.GLES30
import android.opengl.GLSurfaceView
import android.util.Log
import androidx.compose.ui.geometry.Offset
import com.minininja.learngles.GLActivity
import com.minininja.learngles.Layer3DTouchCallback
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class BasicGlesActivity : GLActivity() {
    override fun createRenderer(): GLSurfaceView.Renderer {
        return object : GLSurfaceView.Renderer {
            override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
                GLES30.glClearColor(0.1f, 0.2f, 0.3f, 1.0f)
            }

            override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
                GLES30.glViewport(0, 0, width, height)
            }

            override fun onDrawFrame(gl: GL10?) {
                GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT or GLES30.GL_DEPTH_BUFFER_BIT)
            }
        }
    }

    override fun createTouchCallback(): Layer3DTouchCallback {
        return object : Layer3DTouchCallback {
            override fun onSingleTouch(disX: Float, disY: Float) {
                Log.d("BasicGlesActivity", "Custom SingleTouch: $disX, $disY")
                glSurfaceView?.requestRender()
            }

            override fun onZooming(prevDistance: Float, distance: Float) {
                Log.d("BasicGlesActivity", "Custom Zooming: $distance")
                glSurfaceView?.requestRender()
            }

            override fun onTwoFingersRotating(angle: Float) {
                Log.d("BasicGlesActivity", "Custom Rotating: $angle")
                glSurfaceView?.requestRender()
            }

            override fun onMoving(prevCenter: Offset, centerPoint: Offset) {
                Log.d("BasicGlesActivity", "Custom Moving: $centerPoint")
                glSurfaceView?.requestRender()
            }

            override fun onLongPress(event: Offset) {
                Log.d("BasicGlesActivity", "Custom LongPress at: $event")
            }

            override fun onSingleClick(event: Offset) {
                Log.d("BasicGlesActivity", "Custom SingleClick at: $event")
            }

            override fun onDoubleClick(event: Offset) {
                Log.d("BasicGlesActivity", "Custom DoubleClick at: $event")
            }

            override fun onActionUp(event: Offset) {
                Log.d("BasicGlesActivity", "Custom ActionUp")
            }

            override fun onTwoFingersClick() {
                Log.d("BasicGlesActivity", "Custom TwoFingersClick")
            }

            override fun onThreeFingersClick() {
                Log.d("BasicGlesActivity", "Custom ThreeFingersClick")
            }
        }
    }
}
