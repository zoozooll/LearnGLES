package com.example.learngles

import android.content.Context
import android.os.Handler
import android.os.Message
import android.util.AttributeSet
import android.util.Log
import android.view.MotionEvent
import android.view.View
import androidx.annotation.MainThread

class LongPressView @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null,
    defStyleAttr: Int = 0,
    defStyleRes: Int = 0
) : View(context, attrs, defStyleAttr, defStyleRes) {


    var callback: (() -> Unit)?  = null


    private val eventHandler = object: Handler(context.mainLooper) {
        override fun handleMessage(msg: Message) {
            when(msg.what) {
                EVENT_LONG_PRESS -> {
                    if (isPressed) {
                        callback?.invoke()
                        removeMessages(EVENT_LONG_PRESS)
                        sendEmptyMessageDelayed(EVENT_LONG_PRESS, 20L)
                    }
                }
            }
        }
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        if (((event?.action ?: -1) and MotionEvent.ACTION_MASK) == MotionEvent.ACTION_UP) {
            eventHandler.removeMessages(EVENT_LONG_PRESS)
        }
        return super.onTouchEvent(event)
    }

    override fun setOnLongClickListener(l: OnLongClickListener?) {
        eventHandler.sendEmptyMessage(EVENT_LONG_PRESS)
        true
    }

    companion object {
        private const val EVENT_LONG_PRESS = 1
    }
}