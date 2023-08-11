package com.example.learngles

import android.opengl.GLSurfaceView
import android.opengl.GLSurfaceView.RENDERMODE_CONTINUOUSLY
import android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY
import android.opengl.GLSurfaceView.Renderer
import android.os.Bundle
import android.util.Log
import android.view.GestureDetector
import android.view.MotionEvent
import android.view.SurfaceHolder
import androidx.appcompat.app.AppCompatActivity
import com.example.learngles.databinding.ActivityGldetailBinding
import javax.microedition.khronos.egl.EGL10
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.egl.EGLContext
import javax.microedition.khronos.egl.EGLDisplay
import javax.microedition.khronos.opengles.GL10


class GLDetailActivity : AppCompatActivity(), Renderer {

    private lateinit var binding: ActivityGldetailBinding
    private lateinit var tutorialArg: String

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
            setRenderer(this@GLDetailActivity)
            renderMode = RENDERMODE_CONTINUOUSLY
        }
        val gestureDetector = GestureDetector(this, object: GestureDetector.SimpleOnGestureListener() {
            private var lastScrollX: Float = -Float.MAX_VALUE
            private var lastScrollY: Float = -Float.MAX_VALUE

            private var lastScrollX1: Float = -Float.MAX_VALUE
            private var lastScrollY1: Float = -Float.MAX_VALUE

            override fun onDown(e: MotionEvent): Boolean {
//                Log.i(TAG, "onDown")
                return true
            }

            override fun onShowPress(e: MotionEvent) {
//                Log.i(TAG, "onShowPress")
            }

            override fun onSingleTapUp(e: MotionEvent): Boolean {
//                Log.i(TAG, "onSingleTapUp");
                return false
            }

            override fun onScroll(
                e1: MotionEvent,
                e2: MotionEvent,
                distanceX: Float,
                distanceY: Float
            ): Boolean {
//                Log.i(TAG, "onScroll e1: (${e1.x}, ${e1.y}) e2: (${e2.x}, ${e2.y}) ${e2.pointerCount}")
                if (e2.pointerCount == 1) {
                    if (lastScrollX >= 0 && lastScrollY >= 0) {
                        onSingleMove(lastScrollX, lastScrollY, e2.x, e2.y)
                    }
                    lastScrollX = e2.x
                    lastScrollY = e2.y
                } else if (e2.pointerCount == 2) {
                    if (lastScrollX >= 0 && lastScrollY >= 0 && lastScrollX1 >= 0 && lastScrollY1 >= 0)
                        onTwoFingerMove(lastScrollX, lastScrollY, lastScrollX1, lastScrollY1,
                            e2.getX(0), e2.getY(0), e2.getX(1), e2.getY(1))
                    lastScrollX = e2.getX(0)
                    lastScrollY = e2.getY(0)
                    lastScrollX1 = e2.getX(1)
                    lastScrollY1 = e2.getY(1)
                }
                return true
            }

            override fun onLongPress(e: MotionEvent) {
                onLongPress(e.x, e.y)
//                Log.i(TAG, "onLongPress")
            }

            override fun onFling(
                e1: MotionEvent,
                e2: MotionEvent,
                velocityX: Float,
                velocityY: Float
            ): Boolean {
//                Log.i(TAG, "onFling")
                return true;
            }

            override fun onSingleTapConfirmed(e: MotionEvent): Boolean {
//                Log.i(TAG, "onSingleTapConfirmed")
                onSingleClick(e.x, e.y)
                return false
            }

            override fun onDoubleTap(e: MotionEvent): Boolean {
//                Log.i(TAG, "onDoubleTap")
                onDoubleClick(e.x, e.y)
                return true
            }

            override fun onDoubleTapEvent(e: MotionEvent): Boolean {
//                Log.i(TAG, "onDoubleTapEvent")
                return true
            }

        })
        binding.surfaceSupportedView.setOnTouchListener { v, event ->
//            Log.i(TAG, "onTouch ${event.action}: ${event.pointerCount}")
            gestureDetector.onTouchEvent(event)
        }
    }

    fun onSingleClick(x: Float, y: Float) {
        Log.i(TAG, "onSingleClick")
    }

    fun onDoubleClick(x: Float, y: Float) {
        Log.i(TAG, "onDoubleClick")
    }

    fun onLongPress(x: Float, y: Float) {
        Log.i(TAG, "onLongPress")
    }

    fun onSingleMove(startX: Float, startY: Float, endX: Float, endY: Float) {
        Log.i(TAG, "onSingleMove")
        binding.surfaceSupportedView.queueEvent {

        }
    }

    fun onTwoFingerMove(startX0: Float, startY0: Float, startX1: Float, startY1: Float,
                        endX0: Float, endY0: Float, endX1: Float, endY1: Float) {
        Log.i(TAG, "onTwoFingerMove")
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

    companion object {
        private const val TAG = "GLDetailActivity"
    }
}
