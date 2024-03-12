package com.example.learngles.ui.exercises

import android.opengl.GLSurfaceView
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.example.learngles.MainActivity
import com.example.learngles.NativeLibHelper
import com.example.learngles.R
import com.example.learngles.databinding.ActivityTransformExer2Binding
import javax.microedition.khronos.egl.EGL10
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.egl.EGLContext
import javax.microedition.khronos.egl.EGLDisplay
import javax.microedition.khronos.opengles.GL10

class TransformExer2Activity : AppCompatActivity(), GLSurfaceView.Renderer {

    private lateinit var binding: ActivityTransformExer2Binding
    private lateinit var tutorialArg: String
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        tutorialArg = intent.getStringExtra(MainActivity.KEY_TUTORIAL_TITLE) ?: ""
        binding = ActivityTransformExer2Binding.inflate(layoutInflater);
        setContentView(binding.root)
        binding.surfaceSupportedView.apply {
            preserveEGLContextOnPause = true
            setEGLContextClientVersion(3)
            setEGLContextFactory(object : GLSurfaceView.EGLContextFactory {
                override fun createContext(
                    egl: EGL10,
                    display: EGLDisplay?,
                    eglConfig: EGLConfig?
                ): EGLContext? {
                    val EGL_CONTEXT_CLIENT_VERSION = 0x3098
                    val attrib_list = intArrayOf(
                        EGL_CONTEXT_CLIENT_VERSION,
                        3,
                        EGL10.EGL_NONE
                    )
                    return egl.eglCreateContext(
                        display,
                        eglConfig,
                        EGL10.EGL_NO_CONTEXT,
                        attrib_list
                    )
                }

                override fun destroyContext(
                    egl: EGL10,
                    display: EGLDisplay?,
                    context: EGLContext?
                ) {
                    NativeLibHelper.nativeDestroy()
                    egl.eglDestroyContext(display, context)
                }
            })
            setRenderer(this@TransformExer2Activity)
            renderMode = GLSurfaceView.RENDERMODE_WHEN_DIRTY
        }
        binding.sliderbarTranslateX.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("translate_x" to v))
            binding.surfaceSupportedView.requestRender()
        }
        binding.sliderbarTranslateX.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("translate_x" to v))
            binding.surfaceSupportedView.requestRender()
        }
        binding.sliderbarTranslateY.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("translate_y" to v))
            binding.surfaceSupportedView.requestRender()
        }
        binding.sliderbarTranslateZ.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("translate_z" to v))
            binding.surfaceSupportedView.requestRender()
        }
        binding.sliderbarRotateX.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("rotate_x" to v))
            binding.surfaceSupportedView.requestRender()
        }
        binding.sliderbarRotateY.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("rotate_y" to v))
            binding.surfaceSupportedView.requestRender()
        }
        binding.sliderbarRotateZ.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("rotate_z" to v))
            binding.surfaceSupportedView.requestRender()
        }
        binding.sliderbarScaleX.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("scale_x" to v))
            binding.surfaceSupportedView.requestRender()
        }
        binding.sliderbarScaleY.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("scale_y" to v))
            binding.surfaceSupportedView.requestRender()
        }
        binding.sliderbarScaleZ.callback = { v ->
            NativeLibHelper.sendCommands(mapOf("scale_z" to v))
            binding.surfaceSupportedView.requestRender()
        }
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        NativeLibHelper.nativeSurfaceCreate(tutorialArg)
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        NativeLibHelper.nativeSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        NativeLibHelper.nativeDraw()
    }

    companion object {
        private const val TAG = "TransformExer2Activity"
    }
}