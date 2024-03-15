package com.example.learngles

import android.content.Context
import android.util.AttributeSet
import android.view.LayoutInflater
import android.view.MotionEvent
import androidx.constraintlayout.widget.ConstraintLayout
import com.example.learngles.databinding.TwoArrowBarBinding

class TwoArrowBar @JvmOverloads constructor(context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0) :
    ConstraintLayout(context, attrs, defStyleAttr) {

    var callback: Callback? = null

    private val binding = TwoArrowBarBinding.inflate(LayoutInflater.from(context), this)
        init {

            val ta = context.obtainStyledAttributes(attrs, R.styleable.TwoArrowBar)
            try {
                val title = ta.getString(R.styleable.TwoArrowBar_title)
                binding.title.text = title
            } finally {
                ta.recycle()
            }

            binding.btnSubmit.setOnClickListener {
                callback?.onSubmit()
            }

            binding.btnAdd.setOnClickListener {
                callback?.onAdd()
            }

            binding.btnSubmit.setOnTouchListener { v, event ->
                when (event.action) {
                    MotionEvent.ACTION_DOWN -> {}
                    MotionEvent.ACTION_UP -> {
                       if (v.performClick()) {
                           true
                       }
                    }

                    else -> {}
                }
                true
            }
        }

    interface Callback {
        fun onSubmit()

        fun onAdd()
    }

}