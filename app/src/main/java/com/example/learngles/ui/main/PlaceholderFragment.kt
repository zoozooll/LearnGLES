package com.example.learngles.ui.main

import android.content.Intent
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.learngles.DataSet
import com.example.learngles.GLDetailActivity
import com.example.learngles.MainActivity
import com.example.learngles.databinding.FragmentMainBinding

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
            ContactsAdapter(
                it
            )
        }
        binding.listSection.adapter = listAdapter
        return root
    }

    inner class ContactsAdapter(private val dataList: List<String>) : RecyclerView.Adapter<RecyclerView.ViewHolder>()
    {


        inner class GroupViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
            val textView = itemView.findViewById<TextView>(android.R.id.text1)
            init {
                itemView.setBackgroundResource(android.R.color.holo_purple)
            }
        }

        inner class TutorialViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
            val text1 = itemView.findViewById<TextView>(android.R.id.text1)
            val text2 = itemView.findViewById<TextView>(android.R.id.text2)
            init {
                itemView.setOnClickListener {
                    val intent = Intent(requireContext(), GLDetailActivity::class.java)
                    intent.putExtra(MainActivity.KEY_TUTORIAL_TITLE, text1.text.toString())
                    startActivity(intent)
                }
            }
        }

        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
            val context = parent.context
            val inflater = LayoutInflater.from(context)
            val itemView = inflater.inflate(android.R.layout.simple_list_item_2, parent, false)
            return TutorialViewHolder(itemView)
        }

        override fun onBindViewHolder(viewHolder: RecyclerView.ViewHolder, position: Int) {
            if (viewHolder is GroupViewHolder) {
                viewHolder.textView.text = dataList[position]
            } else if (viewHolder is TutorialViewHolder) {
                viewHolder.text1.text = dataList[position]
            }
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