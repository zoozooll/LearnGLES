package com.example.learngles

import android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY
import android.opengl.GLSurfaceView.Renderer
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.SurfaceHolder
import com.example.learngles.databinding.ActivityGldetailBinding
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10


class GLDetailActivity : AppCompatActivity(), Renderer {

    private lateinit var binding: ActivityGldetailBinding
    private lateinit var surfaceHolder: SurfaceHolder

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityGldetailBinding.inflate(layoutInflater)
        setContentView(binding.root)
        val tutorialArg = intent.getStringExtra(MainActivity.KEY_TUTORIAL_TITLE)
        Log.i("GLDetailActivity", "tutorialArg $tutorialArg")
        binding.surfaceSupportedView.apply {
            preserveEGLContextOnPause = true
            setEGLContextClientVersion(3)
            setRenderer(this@GLDetailActivity)
            renderMode = RENDERMODE_WHEN_DIRTY
        }
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        NativeLibHelper.nativeSurfaceCreate()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        NativeLibHelper.nativeSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        NativeLibHelper.nativeDraw()
    }


}