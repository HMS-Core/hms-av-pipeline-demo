package com.huawei.hms.avpipeline.sample;

import android.util.Log;
import android.widget.CompoundButton;

import com.huawei.hms.avpipeline.api.MediaMeta;

public class PlayerActivitySRdisabled extends PlayerActivity {
    private static final String TAG = "AVP-PlayerActivitySRdisabled";

    @Override
    protected void initAllView() {
        super.initAllView();
        mSwitch.setChecked(false);
        mSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if (mPlayer == null) {
                    return;
                }
                if (isFastClick()) {
                    Log.w(TAG, "onCheckedChanged: click too fast, now button is "+b);
                    makeToastAndRecordLog(Log.INFO, "click button too fast");
                    mSwitch.setChecked(!b);
                    return;
                }
                Log.i(TAG, "switch SR ? " + b);
                MediaMeta meta = new MediaMeta();
                meta.setInt32(MediaMeta.MEDIA_ENABLE_CV, b ? 1 : 0);
                mPlayer.setParameter(meta);
            }
        });
    }

    @Override
    protected void setGraph() {
        MediaMeta meta = new MediaMeta();
        meta.setString(MediaMeta.MEDIA_GRAPH_PATH, getExternalFilesDir(null).getPath() + "/PlayerGraphCV.xml");
        meta.setInt32(MediaMeta.MEDIA_ENABLE_CV, 0);
        mPlayer.setParameter(meta);
    }
}
