/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of MMAudio
 */
#ifndef MM_AUDIO_H
#define MM_AUDIO_H

#include <cstdbool>
#include <cstdint>
#include <cstdio>
#include <sys/cdefs.h>
#include <sys/types.h>


/* Audio stream types */
enum AudioStreamType {
    AS_TYPE_DEFAULT = -1,   /* *< default audio stream type */
    AS_TYPE_VOICE_CALL = 0, /* *< voice call */
    AS_TYPE_SYSTEM,         /* *< system sound */
    AS_TYPE_RING,           /* *< Ring */
    AS_TYPE_MUSIC,          /* *< Music */
    AS_TYPE_ALARM,          /* *< Alarm */
    AS_TYPE_NOTIFICATION,   /* *< Notification */
    AS_TYPE_CNT,            /* *< end index for the stream type visible to app developer */
};

struct VolumeInfo {
    double left;
    double right;
};

enum snd_format_pcm_sub_fmt_t {
    SND_FORMAT_PCM_SUB_16_BIT = 1,    /* *< Signed 16 bits */
    SND_FORMAT_PCM_SUB_8_BIT,         /* *< Unsigned 8 bits */
    SND_FORMAT_PCM_SUB_32_BIT,        /* *< Signed .31 fixed point */
};

enum SoundFormat {
    SND_FORMAT_INVALID = 0xFFFFFFFFUL,   /* *< invalid format */
    SND_FORMAT_DEFAULT = 0x00000000UL,   /* *< */
    SND_FORMAT_PCM = SND_FORMAT_DEFAULT, /* *< */

    // Combinations with sub format field
    SND_FORMAT_PCM_16_BIT = (SND_FORMAT_PCM | SND_FORMAT_PCM_SUB_16_BIT),     /* *< Signed 16 bits */
    SND_FORMAT_PCM_8_BIT = (SND_FORMAT_PCM | SND_FORMAT_PCM_SUB_8_BIT),       /* *< Unsigned 8 bits */
    SND_FORMAT_PCM_32_BIT = (SND_FORMAT_PCM | SND_FORMAT_PCM_SUB_32_BIT),     /* *< Signed .31 fixed point */

};
#endif // MM_AUDIO_H
