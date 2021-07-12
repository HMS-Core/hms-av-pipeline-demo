package com.example.usemediafilter;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "avp-cppdemo";
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("");
        copyFilesFromAssets(this);
        runMediaFilter(getExternalFilesDir(null).getPath());
    }

    public native void runMediaFilter(String path);

    public boolean copyFilesFromAssets(Context ctx) {
        String mDstDir = ctx.getExternalFilesDir(null).getPath();
        AssetManager mManager = ctx.getAssets();
        try {
            String[] lis = mManager.list("");
            for (String item : lis) {
                InputStream is = null;
                try {
                    is = mManager.open(item);
                } catch (FileNotFoundException e) {
                    continue;
                }

                File outFile = new File(mDstDir, item);
                FileOutputStream fos = new FileOutputStream(outFile);
                copy(is, fos);
                is.close();
                fos.close();
            }
        } catch (IOException e) {
            Log.e(TAG, "got error when copy file from assets: " + e);
            e.printStackTrace();
            return false;
        }
        return true;
    }

    private static void copy(InputStream src, OutputStream dst) throws IOException {
        byte[] buf = new byte[8192];
        while (true) {
            int r = src.read(buf);
            if (r == -1) {
                break;
            }
            dst.write(buf, 0, r);
        }
    }
}