package com.example.learngles.ui.main

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.map

class PageViewModel : ViewModel() {

    private val _index = MutableLiveData<String>()
    val text: LiveData<String> = _index.map {
        it
    }

    fun setIndex(index: String) {
        _index.value = index
    }
}