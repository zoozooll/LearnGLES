package com.example.learngles

import android.content.Context
import android.graphics.PointF
import android.os.Message
import android.util.AttributeSet
import android.util.Log
import android.view.GestureDetector
import android.view.MotionEvent
import android.view.View
import kotlin.math.atan2
import kotlin.math.sqrt

class TouchEventView @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null,
    defStyleAttr: Int = 0,
    defStyleRes: Int = 0
) : View(context, attrs, defStyleAttr, defStyleRes) {
    private var lastPoint: PointF = PointF(-Float.MAX_VALUE, -Float.MAX_VALUE)
    private var lastPoint1: PointF = PointF(-Float.MAX_VALUE, -Float.MAX_VALUE)
    private var touchMode = TOUCH_MODE_IDLE

    private var eventTwoFingersTapReady = 0
    private var eventThreeFingersTapReady = 0

    private val eventHandler = object: android.os.Handler(context.mainLooper) {
        override fun handleMessage(msg: Message) {
            when(msg.what) {
                EVENT_MSG_TWOFINGERSTAP_TIMEOUT -> {
                    Log.i(TAG, "handleMessage EVENT_MSG_TWOFINGERSTAP_TIMEOUT")
                    eventTwoFingersTapReady = 0
                    eventThreeFingersTapReady = 0
                }
            }
        }
    }

    var callback:Callback? = null

    private val gestureListener = GestureDetector(context, object: GestureDetector.SimpleOnGestureListener() {
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
            _1: Float,
            _2: Float
        ): Boolean {
//                Log.i(TAG, "onScroll e1: (${e1.x}, ${e1.y}) e2: (${e2.x}, ${e2.y}) ${e2.action}")
            if (e2.pointerCount == 1) {
                if (touchMode == SINGLE_TOUCH && lastPoint.x >= 0 && lastPoint.y >= 0) {
                    val start: PointF = lastPoint;
                    val end: PointF = PointF(e2.x, e2.y)
                    val dis = PointF(end.x - start.x, start.y - end.y)
                    //Log.i(TAG, "onSingleMove: $dis")
                    callback?.onSingleTouch(dis.x, dis.y)
                }
                lastPoint.set(e2.x, e2.y)
                touchMode = SINGLE_TOUCH
            } else if (e2.pointerCount == 2) {
                if (touchMode == TWO_FINGLE_TOUCH && lastPoint.x >= 0 && lastPoint.y >= 0
                    && lastPoint1.x >= 0 && lastPoint1.y >= 0) {
                    val start: PointF = lastPoint
                    val start1: PointF = lastPoint1
                    val end: PointF = PointF(e2.getX(0), e2.getY(0))
                    val end1: PointF = PointF(e2.getX(1), e2.getY(1))
                    val distance =
                        sqrt((end1.x - end.x) * (end1.x - end.x) + (end1.y - end.y) * (end1.y - end.y))
                    val prevDistance =
                        sqrt((start1.x - start.x) * (start1.x - start.x) + (start1.y - start.y) * (start1.y - start.y))
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
                        callback?.onZooming(prevDistance, distance)
                        callback?.onTwoFingersRotating(angle)
                        callback?.onMoving(PointF(prevCenter.x, prevCenter.y),
                            PointF(centerPoint.x, centerPoint.y))
                    }
                }
                lastPoint.set(e2.getX(0), e2.getY(0))
                lastPoint1.set(e2.getX(1), e2.getY(1))
                touchMode = TWO_FINGLE_TOUCH
            }
            return true
        }

        override fun onLongPress(e: MotionEvent) {
            callback?.onLongPress(PointF(e.x, e.y))
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
            callback?.onSingleClick(PointF(e.x, e.y))
            return false
        }

        override fun onDoubleTap(e: MotionEvent): Boolean {
//                Log.i(TAG, "onDoubleTap")
            callback?.onDoubleClick(PointF(e.x, e.y))
            return true
        }

        override fun onDoubleTapEvent(e: MotionEvent): Boolean {
//                Log.i(TAG, "onDoubleTapEvent")
            return true
        }

    })


    override fun onTouchEvent(event: MotionEvent): Boolean {
        when (event.action and MotionEvent.ACTION_MASK) {
            MotionEvent.ACTION_DOWN -> {
                Log.i(TAG, "onTouchEvent DOWN ${event.pointerCount}")
                eventTwoFingersTapReady = 3
                eventThreeFingersTapReady = 3
                eventHandler.sendEmptyMessageDelayed(EVENT_MSG_TWOFINGERSTAP_TIMEOUT, 50L)
            }
            MotionEvent.ACTION_POINTER_DOWN ->{
//                Log.i(TAG, "onTouchEvent ACTION_POINTER_DOWN ${event.pointerCount}")
                if (event.pointerCount == 2) {
                    if (eventThreeFingersTapReady == 3 || eventTwoFingersTapReady == 3) {
                        Log.i(TAG, "onTwoFinglesClick ACTION_POINTER_DOWN ${event.pointerCount}")
                        eventHandler.removeMessages(EVENT_MSG_TWOFINGERSTAP_TIMEOUT)
                        eventHandler.sendEmptyMessageDelayed(EVENT_MSG_TWOFINGERSTAP_TIMEOUT, 300L)
                        if (eventTwoFingersTapReady == 3) {
                            eventTwoFingersTapReady--
                        }
                        if (eventThreeFingersTapReady == 3) {
                            eventThreeFingersTapReady--
                        }
                    }
                } else if (event.pointerCount == 3) {
                    if (eventThreeFingersTapReady == 2) {
                        eventThreeFingersTapReady--
                        Log.i(TAG, "onTwoFinglesClick ACTION_POINTER_DOWN ${event.pointerCount}")
                        eventHandler.removeMessages(EVENT_MSG_TWOFINGERSTAP_TIMEOUT)
                        eventHandler.sendEmptyMessageDelayed(EVENT_MSG_TWOFINGERSTAP_TIMEOUT, 300L)
                    }
                    eventTwoFingersTapReady = 0
                } else {
                    eventHandler.removeMessages(EVENT_MSG_TWOFINGERSTAP_TIMEOUT)
                    eventTwoFingersTapReady = 0
                    eventThreeFingersTapReady = 0
                }
            }
            MotionEvent.ACTION_POINTER_UP -> {
//                Log.i(TAG, "onTouchEvent ACTION_POINTER_UP ${event.pointerCount}")
                if (event.pointerCount == 2) {
                    if (eventTwoFingersTapReady == 2) {
                        eventTwoFingersTapReady--
//                        Log.i(TAG, "onTwoFinglesClick ACTION_POINTER_UP ${event.pointerCount}")
                        eventHandler.removeMessages(EVENT_MSG_TWOFINGERSTAP_TIMEOUT)
                        eventHandler.sendEmptyMessageDelayed(EVENT_MSG_TWOFINGERSTAP_TIMEOUT, 50L)
                    }
//                    eventThreeFingersTapReady = 0
                } else if (event.pointerCount == 3) {
//                    if (eventThreeFingersTapReady == 2) {
//                        eventThreeFingersTapReady--
//                        Log.i(TAG, "onTwoFinglesClick ACTION_POINTER_UP ${event.pointerCount}")
//                        eventHandler.removeMessages(EVENT_MSG_TWOFINGERSTAP_TIMEOUT)
//                        eventHandler.sendEmptyMessageDelayed(EVENT_MSG_TWOFINGERSTAP_TIMEOUT, 50L)
//                    }
//                    eventTwoFingersTapReady = 0
                } else {
                    eventHandler.removeMessages(EVENT_MSG_TWOFINGERSTAP_TIMEOUT)
                    eventTwoFingersTapReady = 0
                    eventThreeFingersTapReady = 0
                }
            }
            MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                Log.i(TAG, "onTouchEvent ACTION_UP_CANCEL ${eventThreeFingersTapReady}")
                if (eventTwoFingersTapReady == 1) {
                    Log.i(TAG, "onTwoFinglesClick ACTION_UP CANCEL TW0_CLICK_EVENT")
                    callback?.onTwoFingersClick()
                }
                if (eventThreeFingersTapReady == 1) {
                    Log.i(TAG, "onTwoFinglesClick ACTION_UP CANCEL THREE_CLICK_EVENT")
                    callback?.onThreeFingersClick()
                }
                eventTwoFingersTapReady = 0
                eventThreeFingersTapReady = 0
                eventHandler.removeMessages(EVENT_MSG_TWOFINGERSTAP_TIMEOUT)
                lastPoint.set(-Float.MAX_VALUE, -Float.MAX_VALUE)
                lastPoint1.set(-Float.MAX_VALUE, -Float.MAX_VALUE)
                callback?.onActionUp(PointF(event.x, event.y))
                touchMode = TOUCH_MODE_IDLE

            }

        }
        return gestureListener.onTouchEvent(event)
    }

    override fun onDetachedFromWindow() {
        super.onDetachedFromWindow()
        eventHandler.removeCallbacksAndMessages(null)
    }

    interface Callback{
        fun onSingleTouch(disX: Float, disY: Float)
        fun onZooming(prevDistance: Float, distance: Float)
        fun onTwoFingersRotating(angle: Float)
        fun onMoving(prevCenter: PointF, centerPoint: PointF)
        fun onLongPress(event: PointF)
        fun onSingleClick(event: PointF)
        fun onDoubleClick(event: PointF)
        fun onActionUp(event:PointF)
        fun onTwoFingersClick()

        fun onThreeFingersClick()
    }

    companion object {
        private const val TAG = "Layer3DTouchView"

        private const val TOUCH_MODE_IDLE = 0
        private const val SINGLE_TOUCH = 1
        private const val TWO_FINGLE_TOUCH = 2

        private const val EVENT_MSG_TWOFINGERSTAP_TIMEOUT = 0X11
    }
}