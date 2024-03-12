package com.example.learngles

import android.content.Context
import android.util.AttributeSet
import android.view.LayoutInflater
import android.view.View
import android.widget.FrameLayout
import androidx.appcompat.content.res.AppCompatResources
import androidx.constraintlayout.widget.ConstraintLayout
import com.example.learngles.databinding.SliderBarBinding
import java.util.Locale

class SliderBar @JvmOverloads constructor(context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0) :
    FrameLayout(context, attrs, defStyleAttr) {

    private lateinit var binding: SliderBarBinding

    var callback: ((Float)->Unit)? = null
    init {
        init(attrs)
    }

    private fun init(attrs: AttributeSet?) {
        binding = SliderBarBinding.inflate(LayoutInflater.from(context), this, true)

        val ta = context.obtainStyledAttributes(attrs, R.styleable.SliderBar)
        try {
            val title = ta.getString(R.styleable.SliderBar_title)
            binding.title.text = title
            val value = ta.getFloat(R.styleable.SliderBar_value, 0f)
            binding.value.text = String.format(Locale.ENGLISH, "%.2f", value)
            binding.sliderValue.value = value
            val minValue = ta.getFloat(R.styleable.SliderBar_min_value, 0f)
            binding.sliderValue.valueFrom = minValue
            val maxValue = ta.getFloat(R.styleable.SliderBar_max_value, 100f)
            binding.sliderValue.valueTo = maxValue
        } finally {
            ta.recycle()
        }
        binding.sliderValue.addOnChangeListener { slider, value, fromUser ->
            if (fromUser) {
                binding.value.text = String.format(Locale.ENGLISH, "%.2f", value)
                callback?.invoke(value)
            }
        }
    }

    fun setValue(v: Float) {
        binding.value.text = String.format(Locale.ENGLISH, "%.2f", v)
        binding.sliderValue.value = v
    }

}