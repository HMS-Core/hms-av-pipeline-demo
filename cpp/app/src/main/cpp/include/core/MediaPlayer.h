/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of media player
 */
#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H
#include <memory>
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include "base/MMAudio.h"
#include <base/MMListener.h>
#include <base/MediaMeta.h>
#include <base/MediaBuffer.h>
#include "base/MediaErrors.h"

namespace AVPipeline {
struct MediaPlayer final {
    enum class PlayerType {
        AUDIO,
        AV,
        MAX_COUNT
    };

    enum EventType {
        MSG_PREPARED = 1,
        MSG_PLAYBACK_COMPLETE = 2,
        MSG_BUFFERING_UPDATE = 3,
        MSG_SEEK_COMPLETE = 4,
        MSG_VIDEO_SIZE = 5,
        MSG_STARTED = 6,
        MSG_PAUSED = 7,
        MSG_STOPPED = 8,
        MSG_ERROR = 100,
        MSG_INFO = 200,
        MSG_DURATION_UPDATE = 300,
        MSG_VIDEO_ROTATION_DEGREE = 502
    };

    enum EventInfoType {
        INFO_UNKNOWN = 1,
        // The player was started as the next player when another player playbak complete
        INFO_STARTED_AS_NEXT = 2,
        // The first video frame is pushed for rendering
        INFO_RENDERING_START = 3,
        // 7xx
        // The video frame can't be deocded fast enough because
        // the video is too complex for the decoder.At this stage, perhaps only the audio plays fine
        INFO_VIDEO_TRACK_LAGGING = 700,
        // In order to buffer more data, the player is internally paused temporarily.
        INFO_BUFFERING_START = 701,
        // The player resume playback after bufferring enough data.
        INFO_BUFFERING_END = 702,
        // The network bandwidth in recent past
        INFO_NETWORK_BANDWIDTH = 703,

        // 8xx
        // If a media has been improperly interleaved or not interleaved at all,
        // e.g has all the video samples first then all the audio
        // ones.This situation is referred to as Bad interleaving.
        // A lot of disk seek may be happening when the video is playing.
        INFO_BAD_INTERLEAVING = 800,
        // The media is not seekable (e.g  the live stream).
        INFO_NOT_SEEKABLE = 801,
        // The new media metadata is available.
        INFO_METADATA_UPDATE = 802,
        // Error occured when seeking
        INFO_SEEK_ERROR = 803,

        // 9xx
        INFO_TIMED_TEXT_ERROR = 900,
    };

    enum InvokeKey {
        INVOKE_ID_GET_TRACK_INFO = 1,
        INVOKE_ID_SELECT_TRACK = 2,
    };

    static std::shared_ptr<MediaPlayer> Create(PlayerType type = PlayerType::AUDIO);
    RetCode SetListener(std::weak_ptr<MMListener> listener);
    RetCode SetDataSource(const std::string &uri, const std::map<std::string, std::string> *headers);
    RetCode SetDataSource(int fd, int64_t offset, int64_t length);
    RetCode SetVideoDisplay(void *handle);
    RetCode Prepare(bool isAsync);
    void Reset();
    RetCode SetVolume(const VolumeInfo &volume);
    RetCode GetVolume(VolumeInfo &volume) const;
    RetCode SetMute(bool mute);
    RetCode GetMute(bool &mute) const;
    RetCode Start();
    RetCode Stop();
    RetCode Pause();
    RetCode Seek(int64_t msec);
    RetCode GetVideoSize(int &width, int &height) const;
    RetCode GetCurrentPosition(int64_t &msec) const;
    RetCode GetDuration(int64_t &msec) const;
    RetCode SetAudioStreamType(AudioStreamType type);
    RetCode GetAudioStreamType(AudioStreamType &type) const;
    RetCode SetParameter(const MediaMetaSP &meta);
    RetCode GetParameter(MediaMetaSP &meta) const;
    RetCode Invoke(const MediaParcelSP &request, MediaParcelSP &reply);

public:
    static const char *GetMsgType(EventType msg);
    static const char *GetInfos(EventInfoType msg);

private:
    MediaPlayer() = default;
    ~MediaPlayer() = default;

private:
    static void Destroy(MediaPlayer *player);
    RetCode Init(PlayerType type);
    void DeInit();

private:
    struct MediaPlayerImpl;
    std::shared_ptr<MediaPlayerImpl> mImpl { nullptr };
    mutable std::mutex mLock;

private:
    DISALLOW_COPY_AND_ASSIGN(MediaPlayer);
};
} // namespace AVPipeline

#endif /* MEDIA_PLAYER_H */
