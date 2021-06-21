/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of media attr
 */
#ifndef MEDIA_ATTR_STR_H
#define MEDIA_ATTR_STR_H


namespace AVPipeline {
extern const char *MEDIA_MIMETYPE_VIDEO_VP8;
extern const char *MEDIA_MIMETYPE_VIDEO_VP9;
extern const char *MEDIA_MIMETYPE_VIDEO_AVC;
extern const char *MEDIA_MIMETYPE_VIDEO_HEVC;
extern const char *MEDIA_MIMETYPE_VIDEO_MPEG4;
extern const char *MEDIA_MIMETYPE_VIDEO_MPEG4V1;
extern const char *MEDIA_MIMETYPE_VIDEO_MPEG4V2;
extern const char *MEDIA_MIMETYPE_VIDEO_MPEG4V3;
extern const char *MEDIA_MIMETYPE_VIDEO_H263;
extern const char *MEDIA_MIMETYPE_VIDEO_H263_P;
extern const char *MEDIA_MIMETYPE_VIDEO_H263_I;
extern const char *MEDIA_MIMETYPE_VIDEO_MPEG2;
extern const char *MEDIA_MIMETYPE_VIDEO_MPEG1;
extern const char *MEDIA_MIMETYPE_VIDEO_H261;
extern const char *MEDIA_MIMETYPE_VIDEO_MJPEG;
extern const char *MEDIA_MIMETYPE_VIDEO_MJPEGB;
extern const char *MEDIA_MIMETYPE_VIDEO_LJPEG;
extern const char *MEDIA_MIMETYPE_VIDEO_JPEGGLS;
extern const char *MEDIA_MIMETYPE_VIDEO_SP5X;
extern const char *MEDIA_MIMETYPE_VIDEO_VC1;
extern const char *MEDIA_MIMETYPE_VIDEO_DV;
extern const char *MEDIA_MIMETYPE_VIDEO_HUFFYUV;
extern const char *MEDIA_MIMETYPE_VIDEO_CYUV;
extern const char *MEDIA_MIMETYPE_VIDEO_INDEOX;
extern const char *MEDIA_MIMETYPE_VIDEO_THEORA;
extern const char *MEDIA_MIMETYPE_VIDEO_DVB;
extern const char *MEDIA_MIMETYPE_VIDEO_RAW;
extern const char *MEDIA_MIMETYPE_CONTAINER_OGG;
extern const char *MEDIA_MIMETYPE_AUDIO_AAC_LATM;
extern const char *MEDIA_MIMETYPE_AUDIO_AMR_NB;
extern const char *MEDIA_MIMETYPE_AUDIO_3GPP;
extern const char *MEDIA_MIMETYPE_AUDIO_WMALOSSLESS;
extern const char *MEDIA_MIMETYPE_AUDIO_AMR_WB;
extern const char *MEDIA_MIMETYPE_AUDIO_WMAPRO;
extern const char *MEDIA_MIMETYPE_AUDIO_MPEG;     // layer III
extern const char *MEDIA_MIMETYPE_AUDIO_MPEG_ADU; // layer III
extern const char *MEDIA_MIMETYPE_AUDIO_MPEG_ON4; // layer III
extern const char *MEDIA_MIMETYPE_AUDIO_WMA;
extern const char *MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_I;
extern const char *MEDIA_MIMETYPE_AUDIO_WAV;
extern const char *MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_II;
extern const char *MEDIA_MIMETYPE_AUDIO_AAC;
extern const char *MEDIA_MIMETYPE_AUDIO_QCELP;
extern const char *MEDIA_MIMETYPE_AUDIO_DRA288;
extern const char *MEDIA_MIMETYPE_AUDIO_VORBIS;
extern const char *MEDIA_MIMETYPE_AUDIO_DRA144;
extern const char *MEDIA_MIMETYPE_AUDIO_OPUS;
extern const char *MEDIA_MIMETYPE_AUDIO_DTSHD;
extern const char *MEDIA_MIMETYPE_AUDIO_G711_ALAW;
extern const char *MEDIA_MIMETYPE_AUDIO_APE;
extern const char *MEDIA_MIMETYPE_AUDIO_EC3;
extern const char *MEDIA_MIMETYPE_AUDIO_G711_MLAW;
extern const char *MEDIA_MIMETYPE_AUDIO_AC3;
extern const char *MEDIA_MIMETYPE_AUDIO_RAW;
extern const char *MEDIA_MIMETYPE_AUDIO_MSGSM;
extern const char *MEDIA_MIMETYPE_AUDIO_FLAC;
extern const char *MEDIA_MIMETYPE_AUDIO_DTS;

extern const char *MEDIA_ATTR_FILE_MAJOR_BAND;

extern const char *MEDIA_ATTR_MIME;
extern const char *MEDIA_ATTR_CONTAINER;
extern const char *MEDIA_ATTR_CODECID;
extern const char *MEDIA_ATTR_CODECTAG;
extern const char *MEDIA_ATTR_CODECPROFILE;
extern const char *MEDIA_ATTR_CODEC_CONTEXT;
extern const char *MEDIA_ATTR_CODEC_CONTEXT_MUTEX;
extern const char *MEDIA_ATTR_TARGET_TIME;

// node mime
extern const char *MEDIA_MIMETYPE_MEDIA_DEMUXER;

// media attributes
extern const char *MEDIA_ATTR_AAC_PROFILE;
extern const char *MEDIA_ATTR_BIT_RATE;
extern const char *MEDIA_ATTR_BIT_RATE_AUDIO;
extern const char *MEDIA_ATTR_BIT_RATE_VIDEO;
extern const char *MEDIA_ATTR_BIT_DEPTH;
extern const char *MEDIA_ATTR_CHANNEL_COUNT;
extern const char *MEDIA_ATTR_CHANNEL_MASK;
extern const char *MEDIA_ATTR_SAMPLE_FORMAT;
extern const char *MEDIA_ATTR_COLOR_FORMAT;
extern const char *MEDIA_ATTR_COLOR_FOURCC;
extern const char *MEDIA_ATTR_DURATION;
extern const char *MEDIA_ATTR_NUM_FRAMES;
extern const char *MEDIA_ATTR_FRAME_RATE;
extern const char *MEDIA_ATTR_HEIGHT;
extern const char *MEDIA_ATTR_IS_ADTS;
extern const char *MEDIA_ATTR_I_FRAME_INTERVAL;
extern const char *MEDIA_ATTR_LANGUAGE;
extern const char *MEDIA_ATTR_MAX_HEIGHT;
extern const char *MEDIA_ATTR_SLICE_HEIGHT;
extern const char *MEDIA_ATTR_MAX_INPUT_SIZE;
extern const char *MEDIA_ATTR_MAX_WIDTH;
extern const char *MEDIA_ATTR_PUSH_BLANK_BUFFERS_ON_STOP;
extern const char *MEDIA_ATTR_SAMPLE_RATE;
extern const char *MEDIA_ATTR_WIDTH;
extern const char *MEDIA_ATTR_STRIDE;
extern const char *MEDIA_ATTR_STRIDE_X;
extern const char *MEDIA_ATTR_STRIDE_Y;
extern const char *MEDIA_ATTR_CROP_RECT;
extern const char *MEDIA_ATTR_VOLUME;
extern const char *MEDIA_ATTR_AVG_FRAMERATE;
extern const char *MEDIA_ATTR_AVC_PROFILE;
extern const char *MEDIA_ATTR_AVC_LEVEL;
extern const char *MEDIA_ATTR_HEVC_PROFILE;
extern const char *MEDIA_ATTR_HEVC_LEVEL;

extern const char *MEDIA_ATTR_STREAM_INDEX;
extern const char *MEDIA_ATTR_AUDIO_SAMPLES;
extern const char *MEDIA_ATTR_SAMPLE_ASPECT_RATION;
extern const char *MEDIA_ATTR_CHANNEL_LAYOUT;

extern const char *MEDIA_ATTR_MIME_AUDIO_3GPP;
extern const char *MEDIA_ATTR_MIME_AUDIO_QUICKTIME;
extern const char *MEDIA_ATTR_MIME_AUDIO_MP4;
extern const char *MEDIA_ATTR_MIME_VIDEO_3GPP;
extern const char *MEDIA_ATTR_MIME_VIDEO_QUICKTIME;
extern const char *MEDIA_ATTR_MIME_VIDEO_MP4;
extern const char *MEDIA_ATTR_HAS_COVER;
extern const char *MEDIA_ATTR_ATTACHEDPIC;
extern const char *MEDIA_ATTR_ATTACHEDPIC_SIZE;
extern const char *MEDIA_ATTR_ATTACHEDPIC_CODECID;
extern const char *MEDIA_ATTR_ATTACHEDPIC_MIME;
extern const char *MEDIA_ATTR_BUFFER_INDEX;
extern const char *MEDIA_ATTR_IS_VIDEO_RENDER;
extern const char *MEDIA_ATTR_MEDIA_TYPE;
extern const char *MEDIA_ATTR_BLOCK_ALIGN;
extern const char *MEDIA_ATTR_ALBUM_ARTIST;
extern const char *MEDIA_ATTR_EXTRADATA0;
extern const char *MEDIA_ATTR_EXTRADATA1;
extern const char *MEDIA_ATTR_ROTATION; // in degree
extern const char *MEDIA_ATTR_CODEC_DATA;

// Time Base
// type: Fraction
extern const char *MEDIA_ATTR_TIMEBASE;

// Seek whence
// type: int32, it is one of the following: SEEK_SET, SEEK_CUR, SEEK_END
extern const char *MEDIA_ATTR_STREAM_IS_SEEKABLE;
extern const char *MEDIA_ATTR_SET_LOOP;

extern const char *MEDIA_ATTR_START_TIME;

extern const char *MEDIA_ATTR_VIDEO_SURFACE;
extern const char *MEDIA_ATTR_BUFFERING_HIGH_BAR;

extern const char *MEDIA_ASSETS_PATH_PREFIX;
extern const char *MEDIA_GRAPH_PATH;
extern const char *MEDIA_ENABLE_CV;
extern const char *MEDIA_BUFFER_NOTIFY;
extern const char *MEDIA_EVENT_NOTIFY;
extern const char *MEDIA_PRIVATE_DATA;

} // namespace AVPipeline

#endif // MEDIA_ATTR_STR_H
