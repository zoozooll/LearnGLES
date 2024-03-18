package com.example.learngles

import android.annotation.SuppressLint
import android.content.Context
import android.content.res.TypedArray
import android.graphics.Bitmap
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.drawable.BitmapDrawable
import android.graphics.drawable.Drawable
import android.os.Handler
import android.util.AttributeSet
import android.util.Log
import android.view.LayoutInflater
import android.view.MotionEvent
import android.view.View
import android.view.ViewConfiguration
import androidx.constraintlayout.widget.ConstraintLayout
import com.example.learngles.databinding.HorizontalJoystickViewBinding
import com.example.learngles.databinding.TwoArrowBarBinding

@SuppressLint("ClickableViewAccessibility")
class HorizontalJoystickView @JvmOverloads constructor(context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0) :
    ConstraintLayout(context, attrs, defStyleAttr) {
    var callback: Callback? = null

    private val binding = HorizontalJoystickViewBinding.inflate(LayoutInflater.from(context), this)

    private var value: Float = 0F
    init {

        val ta = context.obtainStyledAttributes(attrs, R.styleable.HorizontalJoystickView)
        try {
            val title = ta.getString(R.styleable.HorizontalJoystickView_title)
            binding.title.text = title
        } finally {
            ta.recycle()
        }

        binding.btnSubmit.callback = object: LongPressView.Callback {
            override fun onPressingStart() {
                value = 0F
                callback?.onStart()
            }

            override fun onPressing() {
                value -= 1f
                callback?.onMove(value)
            }

            override fun onPressingEnd() {
                callback?.onEnd()
                value = 0F
            }

        }

        binding.btnAdd.callback = object: LongPressView.Callback {
            override fun onPressingStart() {
                callback?.onStart()
                value = 0F
            }

            override fun onPressing() {
                value += 1F
                callback?.onMove(value)
            }

            override fun onPressingEnd() {
                callback?.onEnd()
                value = 0F
            }

        }
    }

    companion object {
        private const val TAG = "LongPressView"
    }

    interface Callback {

        fun onStart()
        fun onMove(v: Float)

        fun onEnd()
    }
}