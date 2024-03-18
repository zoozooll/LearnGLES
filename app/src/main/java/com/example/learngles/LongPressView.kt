package com.example.learngles

import android.content.Context
import android.os.Handler
import android.os.Message
import android.util.AttributeSet
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.widget.ImageView
import androidx.annotation.MainThread

class LongPressView @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null,
    defStyleAttr: Int = 0,
) : androidx.appcompat.widget.AppCompatImageView(context, attrs, defStyleAttr) {

    var callback: Callback?  = null
    private var pressing = false

    private val eventHandler = object: Handler(context.mainLooper) {
        override fun handleMessage(msg: Message) {
            when(msg.what) {
                EVENT_LONG_PRESS -> {
                    Log.i(TAG, "onTouchEvent $isPressed")
                    if (pressing) {
                        callback?.onPressing()
                        removeMessages(EVENT_LONG_PRESS)
                        sendEmptyMessageDelayed(EVENT_LONG_PRESS, 20L)
                    }
                }
            }
        }
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        Log.i(TAG, "onTouchEvent ${event?.action}")
        when((event?.action ?: -1) and MotionEvent.ACTION_MASK) {
            MotionEvent.ACTION_DOWN -> {
                pressing = true
                eventHandler.sendEmptyMessage(EVENT_LONG_PRESS)
                callback?.onPressingStart()
                return true
            }
            MotionEvent.ACTION_UP, MotionEvent.ACTION_CANCEL -> {
                pressing = false
                eventHandler.removeMessages(EVENT_LONG_PRESS)
                callback?.onPressingEnd()
                return false
            }
        }
        return true
    }

    companion object {
        private const val TAG = "LongPressView"
        private const val EVENT_LONG_PRESS = 1
    }

    interface Callback {

        fun onPressingStart()
        fun onPressing()

        fun onPressingEnd()
    }
}