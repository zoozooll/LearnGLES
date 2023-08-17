package com.example.learngles

import android.annotation.SuppressLint
import android.graphics.PointF
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
import kotlin.math.atan2
import kotlin.math.sqrt


class GLDetailActivity : AppCompatActivity(), Renderer {

    private lateinit var binding: ActivityGldetailBinding
    private lateinit var tutorialArg: String

    private lateinit var gestureListener: GestureDetector

    private var lastPoint: PointF = PointF(-Float.MAX_VALUE, -Float.MAX_VALUE)
    private var lastPoint1: PointF = PointF(-Float.MAX_VALUE, -Float.MAX_VALUE)

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
            setRenderer(this@GLDetailActivity)
            renderMode = RENDERMODE_CONTINUOUSLY
        }

        gestureListener = GestureDetector(this, object: GestureDetector.SimpleOnGestureListener() {


            override fun onDown(e: MotionEvent): Boolean {
//                Log.i(TAG, "onDown")
                return true
            }

            override fun onShowPress(e: MotionEvent) {
//                Log.i(TAG, "onShowPress")
            }

            override fun onSingleTapUp(e: MotionEvent): Boolean {
//                Log.i(TAG, "onSingleTapUp")
                return false
            }

            override fun onScroll(
                e1: MotionEvent,
                e2: MotionEvent,
                distanceX: Float,
                distanceY: Float
            ): Boolean {
//                Log.i(TAG, "onScroll e1: (${e1.x}, ${e1.y}) e2: (${e2.x}, ${e2.y}) ${e2.action}")
                if (e2.pointerCount == 1) {
                    if (lastPoint.x >= 0 && lastPoint.y >= 0) {
                        onSingleMove(lastPoint, PointF(e2.x, e2.y))
                    }
                    lastPoint.set(e2.x, e2.y)
                } else if (e2.pointerCount == 2) {
                    if (lastPoint.x >= 0 && lastPoint.y >= 0 && lastPoint1.x >= 0 && lastPoint1.y >= 0) {
                        onTwoFingerMove(lastPoint, lastPoint1,
                            PointF(e2.getX(0), e2.getY(0)),
                            PointF(e2.getX(1), e2.getY(1)),
                            PointF(e1.getX(0), e1.getY(0)),
                            PointF(e1.getX(1), e1.getY(1)))
                    }
                    lastPoint.set(e2.getX(0), e2.getY(0))
                    lastPoint1.set(e2.getX(1), e2.getY(1))
                }
                return true
            }

            override fun onLongPress(e: MotionEvent) {
                onLongPress(PointF(e.x, e.y))
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
                onSingleClick(PointF(e.x, e.y))
                return false
            }

            override fun onDoubleTap(e: MotionEvent): Boolean {
//                Log.i(TAG, "onDoubleTap")
                onDoubleClick(PointF(e.x, e.y))
                return true
            }

            override fun onDoubleTapEvent(e: MotionEvent): Boolean {
//                Log.i(TAG, "onDoubleTapEvent")
                return true
            }

        })
        binding.surfaceSupportedView.setOnTouchListener { v, event ->
//            Log.i(TAG, "onTouch ${event.action}: ${event.pointerCount}")
            when (event.action) {
                MotionEvent.ACTION_UP -> {
                    lastPoint.set(-Float.MAX_VALUE, -Float.MAX_VALUE)
                    lastPoint1.set(-Float.MAX_VALUE, -Float.MAX_VALUE)
                }
                MotionEvent.ACTION_POINTER_DOWN -> {

                }
            }
            gestureListener.onTouchEvent(event)
        }
    }

    fun onSingleClick(point: PointF) {
//        Log.i(TAG, "onSingleClick")
        binding.surfaceSupportedView.queueEvent {
            NativeLibHelper.onSingleClick(point.x, point.y)
        }
    }

    fun onDoubleClick(point: PointF) {
//        Log.i(TAG, "onDoubleClick")
        binding.surfaceSupportedView.queueEvent {
            NativeLibHelper.onDoubleClick(point.x, point.y)
        }
    }

    fun onLongPress(point: PointF) {
//        Log.i(TAG, "onLongPress")
        binding.surfaceSupportedView.queueEvent {
            NativeLibHelper.onLongPress(point.x, point.y)
        }
    }

    fun onSingleMove(start: PointF, end: PointF) {
        val dis = PointF(end.x - start.x, end.y - start.y)
        Log.i(TAG, "onSingleMove: $dis")
        binding.surfaceSupportedView.queueEvent {
            NativeLibHelper.onSingleTouch(dis.x, dis.y)
            binding.surfaceSupportedView.requestRender()
        }
    }

    fun onTwoFingerMove(start: PointF, start1: PointF, end: PointF, end1: PointF, down: PointF, down1: PointF) {
//        Log.i(TAG, "onTwoFingerMove point0: ($startX0, $startY0) -> ($endX0, $endY0) " +
//                "point1: ($startX1, $startY1) -> ($endX1, $endY1)")
        val distance = sqrt ((end1.x - end.x) * (end1.x - end.x) + (end1.y - end.y) * (end1.y - end.y))
        val prevDistance = sqrt ((start1.x - start.x) * (start1.x - start.x) + (start1.y - start.y) * (start1.y - start.y))
        val centerPoint = PointF((end.x + end1.x) * .5f, (end.y + end1.y) * .5f)
        val prevCenter = PointF((start.x + start1.x) * .5f, (start.y + start1.y) * .5f)
        val vectorPoint0 = PointF(start1.x - start.x, start1.y - start.y)
        val vectorPoint1 = PointF(end1.x - end.x, end1.y - end.y)
        val rs_a = vectorPoint1.y * vectorPoint0.x - vectorPoint1.x * vectorPoint0.y
        val rs_b = vectorPoint0.x * vectorPoint1.x + vectorPoint0.y * vectorPoint1.y
        val angle = -atan2(rs_a, rs_b)
        Log.i(TAG, "onTwoFingerMove angle: $angle")
        //
        if (prevDistance >= 0) {
            binding.surfaceSupportedView.queueEvent {
                NativeLibHelper.onZooming(prevDistance, distance)
                NativeLibHelper.onTwoFingersRotating(angle)
                NativeLibHelper.onMoving(prevCenter.x, prevCenter.y, centerPoint.x, centerPoint.y)
                binding.surfaceSupportedView.requestRender()
            }
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

    companion object {
        private const val TAG = "GLDetailActivity"
    }
}
