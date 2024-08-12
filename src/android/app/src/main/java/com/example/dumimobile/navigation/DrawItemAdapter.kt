package com.example.dumimobile.navigation

import android.app.Activity
import android.content.Context
import android.media.Image
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.ImageView
import android.widget.TextView
import com.example.dumimobile.R

class DrawItemAdapter(ctx:Context, rscId:Int, data:Array<NavModel>): ArrayAdapter<NavModel>(ctx, rscId, data) {
    val mContext: Context = ctx;
    val layoutRscId: Int = rscId;
    val data: Array<NavModel> = data;

    @Override
    fun getView(pos:Int, convertView:View, parent: ViewGroup): View {
        var listItem = convertView;
        val inflater = (mContext as Activity).layoutInflater;
        listItem = inflater.inflate(layoutRscId, parent, false);

        val viewIcon = listItem.findViewById<ImageView>(R.id.imageViewIcon);
        val textView = listItem.findViewById<TextView>(R.id.textViewName);

        val folder = data[pos];

        viewIcon.setImageResource(folder.iconNo);
        textView.text = folder.navName;

        return listItem;
    }

}