package com.huawei.hms.avpipeline.sample;

import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.huawei.hms.avpipeline.api.MediaMeta;
import com.huawei.hms.avpipeline.api.MediaParcel;
import com.huawei.hms.avpipeline.sdk.MediaPlayer;

public class PlayerActivitySound extends PlayerActivity {
    private static final String TAG = "AVP-PlayerActivitySound";
    private TextView mEventView;
    @Override
    protected void initAllView() {
        super.initAllView();
        mSwitch.setVisibility(View.GONE);
        mEventView = findViewById(R.id.soundEvent);
    }

    @Override
    protected int getPlayerType() {
        return MediaPlayer.PLAYER_TYPE_AUDIO;
    }

    @Override
    protected void setGraph() {
        MediaMeta meta = new MediaMeta();
        meta.setString(MediaMeta.MEDIA_GRAPH_PATH, getExternalFilesDir(null).getPath() + "/AudioPlayerGraphSD.xml");
        mPlayer.setParameter(meta);
    }

    @Override
    protected void setListener() {
        mPlayer.setOnMsgInfoListener(new MediaPlayer.OnMsgInfoListener() {
            @Override
            public void OnMsgInfo(MediaPlayer mp, int param1, int param2, MediaParcel parcel) {
                if (param1 != MediaPlayer.EVENT_INFO_SOUND_SED) return;
                Log.i(TAG, "got sound event:" + param2);
                if (param2 >= 0) {
                    mEventView.setText(MediaPlayer.SoundEvent.values()[param2].name());
                }
            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
        mEventView.setText("");
    }
}
