package com.example.dumimobile

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ListView
import android.widget.TextView
import android.widget.Toolbar
import androidx.appcompat.app.ActionBarDrawerToggle
import androidx.drawerlayout.widget.DrawerLayout
import com.example.dumimobile.databinding.ActivityMainBinding
import com.example.dumimobile.navigation.DrawItemAdapter
import com.example.dumimobile.navigation.NavModel
import kotlinx.coroutines.selects.select

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    lateinit var mNavigationItems: Array<String>;
    lateinit var mDrawerLayout: DrawerLayout;
    lateinit var drawerList: ListView;
    lateinit var toolbar: Toolbar;
    lateinit var drawerTitle: CharSequence;
    lateinit var title: CharSequence;
    lateinit var drawerToggle: ActionBarDrawerToggle;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main);
        drawerTitle = getTitle();
        title = getTitle();
        mNavigationItems = resources.getStringArray(R.array.navigation_drawer_items);
        mDrawerLayout = findViewById(R.id.drawer_layout);
        drawerList = findViewById(R.id.left_drawer)

        setupToolbar();

        val drawItems: Array<NavModel> = arrayOf(
            NavModel(R.drawable.ic_launcher_background, "Dashboard"),
            NavModel(R.drawable.ic_launcher_background, "Network"),
            NavModel(R.drawable.ic_launcher_background, "Library"),
            NavModel(R.drawable.ic_launcher_background, "Designer"),
            NavModel(R.drawable.ic_launcher_background, "Settings")
        );

        supportActionBar?.setDisplayHomeAsUpEnabled(false);
        supportActionBar?.setHomeButtonEnabled(true);

        val adapter = DrawItemAdapter(this, R.layout.list_view_item_row, drawItems);
        drawerList.adapter = adapter;
        drawerList.setOnItemClickListener(DrawerItemClickListener());



//        binding = ActivityMainBinding.inflate(layoutInflater)
//        setContentView(binding.root)

        // Example of a call to a native method
        //binding.sampleText.text = stringFromJNI()
    }

    fun setupToolbar(){

    }

    /**
     * A native method that is implemented by the 'dumimobile' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {

        // Used to load the 'dumimobile' library on application startup.
        init {
            System.loadLibrary("dumimobile")
        }
    }
}

class DrawerItemClickListener: AdapterView.OnItemClickListener{
    override fun onItemClick(parent: AdapterView<*>?, view: View?, pos: Int, id: Long) {
        val selected = parent?.getItemAtPosition(pos) as String;
        //val intent = Intent(this, selected);
    }

}