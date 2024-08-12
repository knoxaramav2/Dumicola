package com.knx.dumimobile.ui.home

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import com.knx.dumimobile.databinding.FragmentHomeBinding

class HomeFragment : Fragment() {
    external fun InitDumicore(): Int
    external fun LogStatic(): Int

    private var _binding: FragmentHomeBinding? = null

    // This property is only valid between onCreateView and
    // onDestroyView.
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val homeViewModel =
            ViewModelProvider(this).get(HomeViewModel::class.java)

        _binding = FragmentHomeBinding.inflate(inflater, container, false)
        val root: View = binding.root

        val textView: TextView = binding.textHome
        homeViewModel.text.observe(viewLifecycleOwner) {
            textView.text = it
        }

        val btn = binding.button;
        btn.setOnClickListener{
            LogStatic()
        };

        return root
    }

    override fun onStart() {
        super.onStart()
        InitDumicore()
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}