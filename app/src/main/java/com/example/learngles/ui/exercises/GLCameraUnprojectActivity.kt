package com.example.learngles.ui.exercises

import android.opengl.GLSurfaceView.Renderer
import android.os.Bundle
import android.view.MotionEvent
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.learngles.R
import com.example.learngles.databinding.ActivityGlcameraUnprojectBinding
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GLCameraUnprojectActivity : BasicDetailActivity() {
    private lateinit var binding: ActivityGlcameraUnprojectBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        binding = ActivityGlcameraUnprojectBinding.inflate(layoutInflater)
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(binding.main) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
        binding.surfaceSupportedView.apply(setupGLView())

        binding.viewTouchEvent.setOnTouchListener { v, event ->

            true
        }
    }

    companion object {
        private const val TAG = "GLDetailActivity"
    }
}