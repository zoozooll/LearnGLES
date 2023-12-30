package com.example.learngles.ui.main

import android.content.Context
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentPagerAdapter
import com.example.learngles.DataSet
import com.example.learngles.R


/**
 * A [FragmentPagerAdapter] that returns a fragment corresponding to
 * one of the sections/tabs/pages.
 */
class SectionsPagerAdapter(private val context: Context, fm: FragmentManager) :
    FragmentPagerAdapter(fm) {

    override fun getItem(position: Int): Fragment {
        return PlaceholderFragment.newInstance(DataSet.initDataMap.keys.elementAt(position))
    }

    override fun getPageTitle(position: Int): CharSequence {
        return DataSet.initDataMap.keys.elementAt(position)
    }

    override fun getCount(): Int {
        return DataSet.initDataMap.size
    }
}