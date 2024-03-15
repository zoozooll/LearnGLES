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
    init {

        val ta = context.obtainStyledAttributes(attrs, R.styleable.HorizontalJoystickView)
        try {
            val title = ta.getString(R.styleable.HorizontalJoystickView_title)
            binding.title.text = title
        } finally {
            ta.recycle()
        }

        binding.btnSubmit.setOnTouchListener { v, event ->
            callback?.onMove(-1f)
            true
        }

        binding.btnAdd.setOnTouchListener { v, event ->
            callback?.onMove(1f)
            true
        }
    }

    interface Callback {
        fun onMove(v: Float)
    }
}