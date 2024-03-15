package com.example.learngles.ui.exercises

import android.opengl.GLSurfaceView
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.example.learngles.MainActivity
import com.example.learngles.NativeLibHelper
import com.example.learngles.R
import com.example.learngles.TwoArrowBar
import com.example.learngles.databinding.ActivityCoordinateSystemExer3Binding
import com.example.learngles.databinding.ActivityTransformExer2Binding
import javax.microedition.khronos.egl.EGL10
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.egl.EGLContext
import javax.microedition.khronos.egl.EGLDisplay
import javax.microedition.khronos.opengles.GL10

class CoordinateSystemExer3Activity : AppCompatActivity(), GLSurfaceView.Renderer {
    private lateinit var binding: ActivityCoordinateSystemExer3Binding
    private lateinit var tutorialArg: String
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        tutorialArg = intent.getStringExtra(MainActivity.KEY_TUTORIAL_TITLE) ?: ""
        binding = ActivityCoordinateSystemExer3Binding.inflate(layoutInflater);
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
            setRenderer(this@CoordinateSystemExer3Activity)
            renderMode = GLSurfaceView.RENDERMODE_WHEN_DIRTY

            binding.sliderbarTranslateX.callback = object: TwoArrowBar.Callback {
                override fun onSubmit() {
                    NativeLibHelper.sendCommands(mapOf("translate_x" to -1F))
                    binding.surfaceSupportedView.requestRender()
                }

                override fun onAdd() {
                    NativeLibHelper.sendCommands(mapOf("translate_x" to 1F))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            binding.sliderbarTranslateY.callback = object: TwoArrowBar.Callback {
                override fun onSubmit() {
                    NativeLibHelper.sendCommands(mapOf("translate_y" to -1F))
                    binding.surfaceSupportedView.requestRender()
                }

                override fun onAdd() {
                    NativeLibHelper.sendCommands(mapOf("translate_y" to 1F))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            binding.sliderbarTranslateZ.callback = object: TwoArrowBar.Callback {
                override fun onSubmit() {
                    NativeLibHelper.sendCommands(mapOf("translate_z" to -1F))
                    binding.surfaceSupportedView.requestRender()
                }

                override fun onAdd() {
                    NativeLibHelper.sendCommands(mapOf("translate_z" to 1F))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            binding.sliderbarRotateX.callback = object: TwoArrowBar.Callback {
                override fun onSubmit() {
                    NativeLibHelper.sendCommands(mapOf("rotate_x" to -1F))
                    binding.surfaceSupportedView.requestRender()
                }

                override fun onAdd() {
                    NativeLibHelper.sendCommands(mapOf("rotate_x" to 1F))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            binding.sliderbarRotateY.callback = object: TwoArrowBar.Callback {
                override fun onSubmit() {
                    NativeLibHelper.sendCommands(mapOf("rotate_y" to -1F))
                    binding.surfaceSupportedView.requestRender()
                }

                override fun onAdd() {
                    NativeLibHelper.sendCommands(mapOf("rotate_y" to 1F))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            binding.sliderbarRotateZ.callback = object: TwoArrowBar.Callback {
                override fun onSubmit() {
                    NativeLibHelper.sendCommands(mapOf("rotate_z" to -1F))
                    binding.surfaceSupportedView.requestRender()
                }

                override fun onAdd() {
                    NativeLibHelper.sendCommands(mapOf("rotate_z" to 1F))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            binding.sliderbarScaleX.callback = object: TwoArrowBar.Callback {
                override fun onSubmit() {
                    NativeLibHelper.sendCommands(mapOf("scale_x" to -1F))
                    binding.surfaceSupportedView.requestRender()
                }

                override fun onAdd() {
                    NativeLibHelper.sendCommands(mapOf("scale_x" to 1F))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            binding.sliderbarScaleY.callback = object: TwoArrowBar.Callback {
                override fun onSubmit() {
                    NativeLibHelper.sendCommands(mapOf("scale_y" to -1F))
                    binding.surfaceSupportedView.requestRender()
                }

                override fun onAdd() {
                    NativeLibHelper.sendCommands(mapOf("scale_y" to 1F))
                    binding.surfaceSupportedView.requestRender()
                }
            }

            binding.sliderbarScaleZ.callback = object: TwoArrowBar.Callback {
                override fun onSubmit() {
                    NativeLibHelper.sendCommands(mapOf("scale_z" to -1F))
                    binding.surfaceSupportedView.requestRender()
                }

                override fun onAdd() {
                    NativeLibHelper.sendCommands(mapOf("scale_z" to 1F))
                    binding.surfaceSupportedView.requestRender()
                }
            }
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
        private const val TAG = "TransformExer3Activity"
    }
}