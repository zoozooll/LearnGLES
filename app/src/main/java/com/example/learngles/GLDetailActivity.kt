package com.example.learngles

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.SurfaceHolder
import com.example.learngles.databinding.ActivityGldetailBinding


class GLDetailActivity : AppCompatActivity(), SurfaceHolder.Callback2 {

    private lateinit var binding: ActivityGldetailBinding
    private lateinit var surfaceHolder: SurfaceHolder

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityGldetailBinding.inflate(layoutInflater)
        setContentView(binding.root)
        val tutorialArg = intent.getStringExtra(MainActivity.KEY_TUTORIAL_TITLE)
        Log.i("GLDetailActivity", "tutorialArg $tutorialArg")

        surfaceHolder = binding.surfaceSupportorView.holder
        surfaceHolder.addCallback(this);
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        NativeLibHelper.nativeSurfaceCreate()
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        NativeLibHelper.nativeSurfaceChanged(width, height)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        NativeLibHelper.nativeSurfaceDestroyed()
    }

    override fun surfaceRedrawNeeded(holder: SurfaceHolder) {
        NativeLibHelper.nativeSurfaceRedrawNeeded()
    }
}