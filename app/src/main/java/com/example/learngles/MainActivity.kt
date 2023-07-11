package com.example.learngles

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.learngles.MainActivity.ContactsAdapter.Companion.TYPE_GROUP

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }



    inner class ContactsAdapter () : RecyclerView.Adapter<ContactsAdapter.ViewHolder>()
    {
        inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {

        }

        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ContactsAdapter.ViewHolder {
            val context = parent.context
            val inflater = LayoutInflater.from(context)
            val contactView = when(viewType) {
                TYPE_GROUP -> {
                    inflater.inflate(android.R.layout.simple_list_item_1, parent, false).apply {
                        setOnClickListener(null)
                    }
                }
                else -> {
                    inflater.inflate(android.R.layout.simple_list_item_2, parent, false).apply {
                        setOnClickListener {
                            startActivity(Intent(this@MainActivity, GLDetailActivity::class.java).apply {
                                putExtra(KEY_TUTORIAL_TITLE, this)
                            })
                        }
                    }
                }
            }
            return ViewHolder(contactView)
        }

        override fun onBindViewHolder(viewHolder: ContactsAdapter.ViewHolder, position: Int) {
            val contact: TutorialBean = mContacts.get(position)
            val textView = viewHolder.nameTextView
            textView.setText(contact.name)
            val button = viewHolder.messageButton
            button.text = if (contact.isOnline) "Message" else "Offline"
            button.isEnabled = contact.isOnline
        }

        override fun getItemCount(): Int {
            return DataSet.initData.size
        }

        override fun getItemViewType(position: Int): Int {
            val item = DataSet.initData[position];
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