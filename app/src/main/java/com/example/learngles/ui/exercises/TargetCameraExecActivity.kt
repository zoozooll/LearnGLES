package com.example.learngles.ui.exercises

import android.annotation.SuppressLint
import android.graphics.PointF
import android.opengl.GLSurfaceView
import android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY
import android.opengl.GLSurfaceView.Renderer
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.example.learngles.MainActivity
import com.example.learngles.NativeLibHelper
import com.example.learngles.TouchEventView
import com.example.learngles.databinding.ActivityGldetailBinding
import javax.microedition.khronos.egl.EGL10
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.egl.EGLContext
import javax.microedition.khronos.egl.EGLDisplay
import javax.microedition.khronos.opengles.GL10

class TargetCameraExecActivity : BasicDetailActivity() {

    private lateinit var binding: ActivityGldetailBinding

    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityGldetailBinding.inflate(layoutInflater)
        setContentView(binding.root)
        binding.surfaceSupportedView.apply(setupGLView())

        binding.viewTouchEvent.callback = object: TouchEventView.Callback {
            override fun onSingleClick(point: PointF) {

            }

            override fun onDoubleClick(point: PointF) {
                Log.i(TAG, "onDoubleClick")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.sendCommands(mapOf("camera_reset" to 1))
                    binding.surfaceSupportedView.requestRender()
                }
            }
            override fun onLongPress(point: PointF) {

            }

            override fun onSingleTouch(disX: Float, disY: Float) {
                Log.i(TAG, "camera_yaw_pitch: $disX, $disY")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.sendCommands(mapOf("camera_yaw_pitch" to floatArrayOf(disX, disY)))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onZooming(prevDistance: Float, distance: Float) {
                if (prevDistance == 0F) {
                    return;
                }
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.sendCommands(mapOf("camera_zoom" to distance / prevDistance))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onTwoFingersRotating(angle: Float) {
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.sendCommands(mapOf("camera_roll" to angle))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onMoving(prevCenter: PointF, centerPoint: PointF) {
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.sendCommands(mapOf("camera_move" to
                            floatArrayOf(centerPoint.x - prevCenter.x, centerPoint.y - prevCenter.y)))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onActionUp(event: PointF) {
            }

            override fun onTwoFingersClick() {
            }

            override fun onThreeFingersClick() {
            }
        }
    }

    companion object {//n
        private const val TAG = "TargetCameraExecActivity"
    }
}
