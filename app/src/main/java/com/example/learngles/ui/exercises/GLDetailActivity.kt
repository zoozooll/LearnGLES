package com.example.learngles.ui.exercises

import android.annotation.SuppressLint
import android.graphics.PointF
import android.os.Bundle
import android.util.Log
import com.example.learngles.NativeLibHelper
import com.example.learngles.TouchEventView
import com.example.learngles.databinding.ActivityGldetailBinding

class GLDetailActivity : BasicDetailActivity() {

    private lateinit var binding: ActivityGldetailBinding

    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityGldetailBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.surfaceSupportedView.apply(setupGLView())

        binding.viewTouchEvent.callback = object: TouchEventView.Callback {
            override fun onSingleClick(point: PointF) {
                Log.i(TAG, "onSingleClick")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onSingleClick(point.x, point.y)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onDoubleClick(point: PointF) {
                Log.i(TAG, "onDoubleClick")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onDoubleClick(point.x, point.y)
                    binding.surfaceSupportedView.requestRender()
                }
            }
            override fun onLongPress(point: PointF) {
                Log.i(TAG, "onLongPress")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onLongPress(point.x, point.y)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onSingleTouch(disX: Float, disY: Float) {
                Log.i(TAG, "onSingleMove: $disX, $disY")
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onSingleTouch(disX, disY)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onZooming(prevDistance: Float, distance: Float) {
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onZooming(prevDistance, distance)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onTwoFingersRotating(angle: Float) {
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onTwoFingersRotating(angle)
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onMoving(prevCenter: PointF, centerPoint: PointF) {
                binding.surfaceSupportedView.queueEvent {
                    NativeLibHelper.onMoving(
                        prevCenter.x,
                        prevCenter.y,
                        centerPoint.x,
                        centerPoint.y
                    )
                    binding.surfaceSupportedView.requestRender()
                }
            }

            override fun onActionUp(event: PointF) {
            }

            override fun onTwoFingersClick() {
            }

            override fun onThreeFingersClick() {
            }
        }
    }


    companion object {//n
        private const val TAG = "GLDetailActivity"
    }
}
