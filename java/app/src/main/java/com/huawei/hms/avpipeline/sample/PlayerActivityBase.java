package com.huawei.hms.avpipeline.sample;

import android.view.View;

public class PlayerActivityBase extends PlayerActivity {
    private static final String TAG = "AVP-PlayerActivityBase";

    @Override
    protected void initAllView() {
        super.initAllView();
        mSwitch.setVisibility(View.GONE);
    }
}
