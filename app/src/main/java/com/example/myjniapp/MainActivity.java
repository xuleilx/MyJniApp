package com.example.myjniapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.example.myjniapp.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    public static final String TAG="MainActivity";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        initCallbacks();
        tv.setText(stringFromJNI());
        int result = add(5,2);
        Log.d(TAG,"Result: "+result);

        activeMessage();
    }

    public void onMessage(String msg) {
        Log.d(TAG,"MacAddress:"+msg);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int add(int x,int y);
    public native void initCallbacks();
    public native void activeMessage();

}