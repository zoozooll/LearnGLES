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

class FocalLengthAndFOVActivity : AppCompatActivity(), Renderer {

    private lateinit var binding: ActivityGldetailBinding
    private lateinit var tutorialArg: String

    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityGldetailBinding.inflate(layoutInflater)
        setContentView(binding.root)
        tutorialArg = intent.getStringExtra(MainActivity.KEY_TUTORIAL_TITLE) ?: ""
        Log.i("GLDetailActivity", "tutorialArg $tutorialArg")
        binding.surfaceSupportedView.apply {
            preserveEGLContextOnPause = true
            setEGLContextClientVersion(3)
            setEGLContextFactory(object : GLSurfaceView.EGLContextFactory {
                override fun createContext(
                    egl: EGL10,
                    display: EGLDisplay?,
                    eglConfig: EGLConfig?
                ): EGLContext? {
                    val EGL_CONTEXT_CLIENT_VERSION = 0x3098
                    val attrib_list = intArrayOf(
                        EGL_CONTEXT_CLIENT_VERSION,
                        3,
                        EGL10.EGL_NONE
                    )
                    return egl.eglCreateContext(
                        display,
                        eglConfig,
                        EGL10.EGL_NO_CONTEXT,
                        attrib_list
                    )
                }

                override fun destroyContext(
                    egl: EGL10,
                    display: EGLDisplay?,
                    context: EGLContext?
                ) {
                    NativeLibHelper.nativeDestroy()
                    egl.eglDestroyContext(display, context)
                }
            })
            setRenderer(this@FocalLengthAndFOVActivity)
            renderMode = RENDERMODE_WHEN_DIRTY
        }

        binding.viewTouchEvent.callback = object: TouchEventView.Callback {
            override fun onSingleClick(point: PointF) {
                Log.i(TAG, "onSingleClick")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onSingleClick(point.x, point.y)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onDoubleClick(point: PointF) {
                Log.i(TAG, "onDoubleClick")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onDoubleClick(point.x, point.y)
                    binding.surfaceSupportedView.requestRender()
                }
            }
            override fun onLongPress(point: PointF) {
                Log.i(TAG, "onLongPress")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onLongPress(point.x, point.y)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onSingleTouch(disX: Float, disY: Float) {
                Log.i(TAG, "onSingleMove: $disX, $disY")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onSingleTouch(disX, disY)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onZooming(prevDistance: Float, distance: Float) {
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onZooming(prevDistance, distance)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onTwoFingersRotating(angle: Float) {
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onTwoFingersRotating(angle)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onMoving(prevCenter: PointF, centerPoint: PointF) {
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onMoving(
                        prevCenter.x,
                        prevCenter.y,
                        centerPoint.x,
                        centerPoint.y
                    )
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

        binding.barSetFov.callback = {
            NativeLibHelper.sendCommands(mapOf("set_fovy" to it))
            binding.surfaceSupportedView.requestRender()
        }
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        NativeLibHelper.nativeSurfaceCreate(tutorialArg)
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        NativeLibHelper.nativeSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        NativeLibHelper.nativeDraw()
    }

    companion object {//n
        private const val TAG = "GLDetailActivity"
    }
}
