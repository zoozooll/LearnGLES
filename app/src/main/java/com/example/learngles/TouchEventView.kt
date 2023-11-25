package com.example.learngles

import android.content.Context
import android.graphics.PointF
import android.util.AttributeSet
import android.util.Log
import android.view.GestureDetector
import android.view.MotionEvent
import android.view.View
import kotlin.math.atan2
import kotlin.math.sqrt

class TouchEventView @JvmOverloads constructor(
    context: Context?,
    attrs: AttributeSet? = null,
    defStyleAttr: Int = 0,
    defStyleRes: Int = 0
) : View(context, attrs, defStyleAttr, defStyleRes) {
    private var lastPoint: PointF = PointF(-Float.MAX_VALUE, -Float.MAX_VALUE)
    private var lastPoint1: PointF = PointF(-Float.MAX_VALUE, -Float.MAX_VALUE)

    var callback:Callback? = null

    private val gestureListener = GestureDetector(context, object: GestureDetector.SimpleOnGestureListener() {
        override fun onDown(e: MotionEvent): Boolean {
            Log.i(TAG, "onDown")
            return true
        }

        override fun onShowPress(e: MotionEvent) {
            Log.i(TAG, "onShowPress")
        }

        override fun onSingleTapUp(e: MotionEvent): Boolean {
            Log.i(TAG, "onSingleTapUp")
            return false
        }

        override fun onScroll(
            e1: MotionEvent,
            e2: MotionEvent,
            distanceX: Float,
            distanceY: Float
        ): Boolean {
            Log.i(TAG, "onScroll e1: (${e1.x}, ${e1.y}) e2: (${e2.x}, ${e2.y}) ${e2.action}")
            if (e2.pointerCount == 1) {
                if (lastPoint.x >= 0 && lastPoint.y >= 0) {
                    callback?.onSingleMove(lastPoint, PointF(e2.x, e2.y))
                }
                lastPoint.set(e2.x, e2.y)
            } else if (e2.pointerCount == 2 ) {
                if (lastPoint.x >= 0 && lastPoint.y >= 0 && lastPoint1.x >= 0 && lastPoint1.y >= 0) {
                    val start = lastPoint
                    val start1 = lastPoint1
                    val end = PointF(e2.getX(0), e2.getY(0))
                    val end1 = PointF(e2.getX(1), e2.getY(1))
                    val distance = sqrt ((end1.x - end.x) * (end1.x - end.x) + (end1.y - end.y) * (end1.y - end.y))
                    val prevDistance = sqrt ((start1.x - start.x) * (start1.x - start.x) + (start1.y - start.y) * (start1.y - start.y))
                    val centerPoint = PointF((end.x + end1.x) * .5f, (end.y + end1.y) * .5f)
                    val prevCenter = PointF((start.x + start1.x) * .5f, (start.y + start1.y) * .5f)
                    val vectorPoint0 = PointF(start1.x - start.x, start1.y - start.y)
                    val vectorPoint1 = PointF(end1.x - end.x, end1.y - end.y)
                    val rs_a = vectorPoint1.y * vectorPoint0.x - vectorPoint1.x * vectorPoint0.y
                    val rs_b = vectorPoint0.x * vectorPoint1.x + vectorPoint0.y * vectorPoint1.y
                    val angle = -atan2(rs_a, rs_b)
                    //
                    if (prevDistance >= 0) {
                            callback?.onZooming(prevDistance, distance)
                            callback?.onTwoFingersRotating(angle)
                            callback?.onMoving(prevCenter.x, prevCenter.y, centerPoint.x, centerPoint.y)
                    }
                }
                lastPoint.set(e2.getX(0), e2.getY(0))
                lastPoint1.set(e2.getX(1), e2.getY(1))
            }
            return true
        }

        override fun onLongPress(e: MotionEvent) {
            callback?.onLongPress(PointF(e.x, e.y))
            Log.i(TAG, "onLongPress")
        }

        override fun onFling(
            e1: MotionEvent,
            e2: MotionEvent,
            velocityX: Float,
            velocityY: Float
        ): Boolean {
            Log.i(TAG, "onFling")
            return true
        }

        override fun onSingleTapConfirmed(e: MotionEvent): Boolean {
            Log.i(TAG, "onSingleTapConfirmed")
            callback?.onSingleClick(PointF(e.x, e.y))
            return false
        }

        override fun onDoubleTap(e: MotionEvent): Boolean {
            Log.i(TAG, "onDoubleTap")
            callback?.onDoubleClick(PointF(e.x, e.y))
            return true
        }

        override fun onDoubleTapEvent(e: MotionEvent): Boolean {
            Log.i(TAG, "onDoubleTapEvent")
            return true
        }

    })


    override fun onTouchEvent(event: MotionEvent): Boolean {
        Log.i(TAG, "onTouch ${event.action}: ${event.pointerCount}")
        when (event.action) {
            MotionEvent.ACTION_UP -> {
                lastPoint.set(-Float.MAX_VALUE, -Float.MAX_VALUE)
                lastPoint1.set(-Float.MAX_VALUE, -Float.MAX_VALUE)
            }
            MotionEvent.ACTION_POINTER_DOWN -> {

            }
        }
        return gestureListener.onTouchEvent(event)
    }

    companion object {
        private const val TAG = "TouchEventView"
    }

    interface Callback {
        fun onSingleClick(point: PointF)

        fun onDoubleClick(point: PointF)

        fun onLongPress(point: PointF)

        fun onSingleMove(start: PointF, end: PointF)

//        fun onTwoFingerMove(start: PointF, start1: PointF, end: PointF, end1: PointF)

        fun onZooming(prevDistance: Float, distance: Float)

        fun onTwoFingersRotating(angle: Float)

        fun onMoving(x: Float, y: Float, x1: Float, y1: Float)
    }

}