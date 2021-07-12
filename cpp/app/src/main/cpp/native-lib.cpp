#include <jni.h>
#include <string>
#include <fstream>
#include <thread>
#include <dlfcn.h>
#include <android/log.h>
#include "base/MediaBuffer.h"
#include "base/MediaAttrStr.h"
#include "base/MediaMeta.h"
#include "core/MediaFilter.h"
#include "core/INode.h"

#undef LOG_TAG
#define LOG_TAG "avp-cppdemo"
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace std;
using namespace AVPipeline;

struct EventListener : MMListener {
    void OnMessage(int msg, int param1, int param2, MediaParcelSP) override
    {
        if (msg == INode::EVENT_INFO) {
            switch (param1) {
                case INode::INFO_SOUND_SED:
                    ALOGD("sound detect result: %d", param2);
                    break;
                default:
                    break;
            }
        }
    }
};

bool ReleaseOutputBuffer(const MediaBuffer *mediaBuffer)
{
    uint8_t *buffer = nullptr;
    bool ret = true;
    if (!(mediaBuffer->GetBufferInfo(reinterpret_cast<uintptr_t *>(&buffer), nullptr, nullptr, 1))) {
        ALOGW("error in release mediabuffer");
        ret = false;
    }
    MM_RELEASE_ARRAY(buffer);
    return ret;
}

void TestSoundDetect(string path)
{
    MediaMetaSP meta = MediaMeta::Create();
    if (meta == nullptr) {
        ALOGE("create MediaMeta failed");
        return;
    }
    meta->SetValue<string>(MEDIA_GRAPH_PATH, path + "/SedPipeline.xml");
    meta->SetValue<string>(MEDIA_ASSETS_PATH_PREFIX, path);
    meta->SetValue<int32_t>(MEDIA_ATTR_SAMPLE_RATE, 32000);
    meta->SetValue<int32_t>(MEDIA_ATTR_CHANNEL_COUNT, 1);
    meta->SetValue<int32_t>(MEDIA_ATTR_SAMPLE_FORMAT, 1); // AV_SAMPLE_FMT_S16
    meta->SetValue<bool>(MEDIA_BUFFER_NOTIFY, false);

    void *phandle = dlopen("libmediafilter.so", RTLD_NOW | RTLD_GLOBAL);
    if (phandle == nullptr) {
        ALOGE("dlopen failed, %s", dlerror());
        return;
    }
    ALOGI("dlopen succ");
    void *sym = dlsym(phandle, "CreateMediaFilter");
    if (sym == nullptr) {
        ALOGE("get symbol failed, %s", dlerror());
        dlclose(phandle);
        return;
    }
    ALOGI("get symbol succ");
    using CreateMediaFilterFunc = shared_ptr<MediaFilter>(*)(const MediaMetaSP &meta);
    auto fun = reinterpret_cast<CreateMediaFilterFunc>(sym);
    shared_ptr<MediaFilter> mFilter = fun(meta);
    if (mFilter == nullptr) {
        ALOGE("create MediaFilter failed");
        dlclose(phandle);
        return;
    }
    ALOGI("create MediaFilter succ");

    shared_ptr<EventListener> listener = make_shared<EventListener>();
    mFilter->SetListener(listener);
    RetCode ret = mFilter->Start();
    if (ret != OK) {
        ALOGE("Start MediaFilter failed");
        dlclose(phandle);
        return;
    }
    ALOGI("Start MediaFilter succ");

    string pcmPath = path + "/alg.pcm";
    ifstream fs(pcmPath, ios::in | ios::binary);
    static constexpr int size = 20 * 32000 / 1000 * sizeof(int16_t);
    int cnt = 0;
    uint64_t pts = 0;
    while (cnt++ < 500) {
        auto *data = new char[size];
        fs.read(data, size);
        MediaBufferSP mediaBuf = MediaBuffer::Create(MediaBuffer::BT_RawAudio);
        if (mediaBuf == nullptr) {
            ALOGE("create MediaBuffer failed");
            dlclose(phandle);
            fs.close();
            return;
        }
        mediaBuf->SetBufferInfo(reinterpret_cast<uintptr_t *>(&data), nullptr, &size, 1);
        mediaBuf->SetSize(size);
        mediaBuf->SetPts(pts);
        mediaBuf->AddReleaseBufferFunc(ReleaseOutputBuffer);
        mFilter->WriteBuffer(mediaBuf, MT_AUDIO);
        pts += 30 * 1000;
    }

    this_thread::sleep_for(5s);
    mFilter->Stop();
    mFilter.reset();
    dlclose(phandle);
    fs.close();
    ALOGI("exit");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_usemediafilter_MainActivity_runMediaFilter(JNIEnv *env, jobject thiz, jstring path)
{
    const char *pathcstr = env->GetStringUTFChars(path, nullptr);
    TestSoundDetect(pathcstr);
    env->ReleaseStringUTFChars(path, pathcstr);
}