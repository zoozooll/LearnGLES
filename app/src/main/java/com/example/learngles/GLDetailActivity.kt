package com.example.learngles

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.example.learngles.databinding.ActivityGldetailBinding


class GLDetailActivity : AppCompatActivity() {

    private lateinit var binding: ActivityGldetailBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityGldetailBinding.inflate(layoutInflater)
        setContentView(binding.root)
        val tutorialArg = intent.getStringExtra(MainActivity.KEY_TUTORIAL_TITLE)
        Log.i("GLDetailActivity", "tutorialArg $tutorialArg")
    }
}