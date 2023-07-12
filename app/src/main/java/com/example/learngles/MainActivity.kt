package com.example.learngles

import android.content.Intent
import android.os.Bundle
import android.view.LayoutInflater
import android.view.SurfaceHolder
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.learngles.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private lateinit var listAdapter: ContactsAdapter



    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.root.layoutManager = LinearLayoutManager(this@MainActivity)
        listAdapter = ContactsAdapter()
        binding.root.adapter = listAdapter
    }



    inner class ContactsAdapter : RecyclerView.Adapter<RecyclerView.ViewHolder>()
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
                    val intent = Intent(this@MainActivity, GLDetailActivity::class.java)
                    intent.putExtra(KEY_TUTORIAL_TITLE, text1.text.toString())
                    startActivity(intent)
                }
            }
        }

        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
            val context = parent.context
            val inflater = LayoutInflater.from(context)
            return when(viewType) {
                TYPE_GROUP -> {
                    val itemView = inflater.inflate(android.R.layout.simple_list_item_1, parent, false)
                    GroupViewHolder(itemView)
                }
                else -> {
                    val itemView = inflater.inflate(android.R.layout.simple_list_item_2, parent, false)
                    TutorialViewHolder(itemView)
                }
            }
        }

        override fun onBindViewHolder(viewHolder: RecyclerView.ViewHolder, position: Int) {
            if (viewHolder is GroupViewHolder) {
                viewHolder.textView.text = DataSet.initData[position]
            } else if (viewHolder is TutorialViewHolder) {
                viewHolder.text1.text = DataSet.initData[position]
            }
        }

        override fun getItemCount(): Int {
            return DataSet.initData.size
        }

        override fun getItemViewType(position: Int): Int {
            val item = DataSet.initData[position]
            return if (item[0].isDigit()) {
                TYPE_GROUP
            } else {
                TYPE_TUTORIAL
            }
        }
    }
    companion object {
        private const val TYPE_GROUP = 1
        private const val TYPE_TUTORIAL = 2

        const val KEY_TUTORIAL_TITLE = "tutorial_title"
    }
}