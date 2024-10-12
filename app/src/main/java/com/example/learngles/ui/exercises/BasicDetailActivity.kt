package com.example.learngles.ui.exercises

import android.opengl.GLSurfaceView
import android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY
import android.opengl.GLSurfaceView.Renderer
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.learngles.MainActivity
import com.example.learngles.NativeLibHelper
import javax.microedition.khronos.egl.EGL10
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.egl.EGLContext
import javax.microedition.khronos.egl.EGLDisplay
import javax.microedition.khronos.opengles.GL10

open class BasicDetailActivity : AppCompatActivity(), Renderer {

    private lateinit var tutorialArg: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        tutorialArg = intent.getStringExtra(MainActivity.KEY_TUTORIAL_TITLE) ?: ""
    }

    protected fun setupGLView(): (GLSurfaceView).() -> Unit = {
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
        setRenderer(this@BasicDetailActivity)
        renderMode = RENDERMODE_WHEN_DIRTY
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

    companion object {//n
        private const val TAG = "BaseDetailActivity"
    }
}