package com.example.learngles.ui.main

import android.content.Intent
import android.os.Bundle
import android.text.TextUtils
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.CheckBox
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.learngles.DataSet
import com.example.learngles.ui.exercises.GLDetailActivity
import com.example.learngles.MainActivity
import com.example.learngles.R
import com.example.learngles.databinding.FragmentMainBinding
import com.example.learngles.ui.exercises.BasicDetailActivity
import com.example.learngles.ui.exercises.CoordinateSystemExer3Activity
import com.example.learngles.ui.exercises.CoordinateSystemExer4Activity
import com.example.learngles.ui.exercises.FocalLengthAndFOVActivity
import com.example.learngles.ui.exercises.SsaoExerActivity
import com.example.learngles.ui.exercises.TargetCameraExecActivity
import com.example.learngles.ui.exercises.TransformExer2Activity

/**
 * A placeholder fragment containing a simple view.
 */
class PlaceholderFragment : Fragment() {

    private lateinit var pageViewModel: PageViewModel
    private var _binding: FragmentMainBinding? = null
    private val binding get() = _binding!!

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        pageViewModel = ViewModelProvider(this)[PageViewModel::class.java].apply {
            setIndex(arguments?.getString(ARG_SECTION) ?: "")
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {

        _binding = FragmentMainBinding.inflate(inflater, container, false)
        val root = binding.root

        binding.listSection.layoutManager = LinearLayoutManager(requireContext())
        val listAdapter = DataSet.initDataMap[arguments?.getString(ARG_SECTION) ?: ""]?.let {
            ContactsAdapter(it)
        }
        binding.listSection.adapter = listAdapter
        return root
    }

    inner class ContactsAdapter(private val dataList: List<Pair<String, String>>) : RecyclerView.Adapter<RecyclerView.ViewHolder>()
    {

        inner class TutorialViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
            val text1 = itemView.findViewById<TextView>(R.id.tvw_title)
            val checkBox = itemView.findViewById<CheckBox>(R.id.check_enable)
            var boundData: Pair<String, String>? = null
            init {
                itemView.setOnClickListener {
                    if (checkBox.isChecked) {
                        try {
                            val tutorialTitle = text1.text.toString();
                            val dstActivity = Class.forName("com.example.learngles.ui.exercises.${boundData?.second}")
                            val intent = Intent(requireContext(), dstActivity)
                            intent.putExtra(MainActivity.KEY_TUTORIAL_TITLE, tutorialTitle)
                            startActivity(intent)
                        } catch (ex: Exception) {
                            ex.printStackTrace()
                        }
                    }
                }
            }
        }

        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
            val context = parent.context
            val inflater = LayoutInflater.from(context)
            val itemView = inflater.inflate(R.layout.listitem_tutorial, parent, false)
            return TutorialViewHolder(itemView)
        }

        override fun onBindViewHolder(viewHolder: RecyclerView.ViewHolder, position: Int) {
            (viewHolder as TutorialViewHolder).text1.text = dataList[position].first
            (viewHolder as TutorialViewHolder).checkBox.isChecked = !TextUtils.isEmpty(dataList[position].second)
            (viewHolder as TutorialViewHolder).boundData = dataList[position]
        }

        override fun getItemCount(): Int {
            return dataList.size
        }
    }

    companion object {
        private const val ARG_SECTION = "section"

        @JvmStatic
        fun newInstance(section: String?): PlaceholderFragment {
            return PlaceholderFragment().apply {
                arguments = Bundle().apply {
                    putString(ARG_SECTION, section)
                }
            }
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}