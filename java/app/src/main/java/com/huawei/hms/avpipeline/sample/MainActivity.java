package com.huawei.hms.avpipeline.sample;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "AVP-MainActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        handlePermission();
        initAllView();
    }

    private void handlePermission() {
        String[] permissionLists = {
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.ACCESS_NETWORK_STATE
        };
        int requestPermissionCode = 1;
        for (String permission : permissionLists) {
            if (ContextCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, permissionLists, requestPermissionCode);
            }
        }
    }

    void initAllView() {
        Button btn1 = findViewById(R.id.asset);
        btn1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, AssetActivity.class);
                startActivity(intent);
            }
        });
        Button btn2 = findViewById(R.id.playerbase);
        btn2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, PlayerActivityBase.class);
                startActivity(intent);
            }
        });
        Button btn3 = findViewById(R.id.playerSRdisabled);
        btn3.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, PlayerActivitySRdisabled.class);
                startActivity(intent);
            }
        });
        Button btn4 = findViewById(R.id.playerSRenabled);
        btn4.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, PlayerActivitySRenabled.class);
                startActivity(intent);
            }
        });
        Button btn5 = findViewById(R.id.playerSD);
        btn5.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, PlayerActivitySound.class);
                startActivity(intent);
            }
        });
    }
}
