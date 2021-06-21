/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: header file of log
 */
#ifndef MM_DEBUG_H
#define MM_DEBUG_H

#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <stdarg.h>
#include <cstring>
#include "osal/log.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EXIT_AND_RETURN_E(_code)           \
    do {                                   \
        ERROR("<<<(status: %d)", (_code)); \
        return (_code);                    \
    } while (0)

#define ENTER_I() INFO(">>>")
#define EXIT_I()      \
    do {              \
        INFO(" <<<"); \
        return;       \
    } while (0)

#define EXIT_AND_RETURN_I(_code)          \
    do {                                  \
        INFO("<<<(status: %d)", (_code)); \
        return (_code);                   \
    } while (0)

#define ENTER_D() DEBUG(">>>")
#define EXIT_D()       \
    do {               \
        DEBUG(" <<<"); \
        return;        \
    } while (0)

#define EXIT_AND_RETURN_D(_code)           \
    do {                                   \
        DEBUG("<<<(status: %d)", (_code)); \
        return (_code);                    \
    } while (0)

#define ENTER_V() VERBOSE(">>>")
#define EXIT_V()         \
    do {                 \
        VERBOSE(" <<<"); \
        return;          \
    } while (0)

#define EXIT_AND_RETURN_V(_code)             \
    do {                                     \
        VERBOSE("<<<(status: %d)", (_code)); \
        return (_code);                      \
    } while (0)

#ifndef MM_FOURCC
#define MM_FOURCC(ch0, ch1, ch2, ch3)                                                                \
    ((uint32_t)(uint8_t)(ch0) | ((uint32_t)(uint8_t)(ch1) << 8) | ((uint32_t)(uint8_t)(ch2) << 16) | \
        ((uint32_t)(uint8_t)(ch3) << 24))
#endif

#ifndef DEBUG_FOURCC
#define DEBUG_FOURCC(preStr, fourcc)                                                                      \
    do {                                                                                                  \
        uint32_t i_fourcc = fourcc;                                                                       \
        char *ptr = (char *)(&(i_fourcc));                                                                \
        DEBUG("%s fourcc: 0x%x, %c%c%c%c", preStr, i_fourcc, *(ptr), *(ptr + 1), *(ptr + 2), *(ptr + 3)); \
    } while (0)
#endif

#ifndef ASSERT
#define ASSERT(expr)             \
    do {                         \
        if (!(expr)) {           \
            assert(0 && (expr)); \
        }                        \
    } while (0)
#endif
#ifndef ASSERT_EQ
#define ASSERT_EQ(expr1, expr2)                \
    do {                                       \
        if ((expr1) != (expr2)) {              \
            assert(0 && ((expr1) == (expr2))); \
        }                                      \
    } while (0)
#endif
#ifndef ASSERT_ERROR
#define ASSERT_ERROR(expr, msg)  \
    do {                         \
        if (!(expr)) {           \
            ERROR(msg);          \
            assert(0 && (expr)); \
        }                        \
    } while (0)
#endif

#ifndef ASSERT_RET
#define ASSERT_RET(expr, ret)    \
    do {                         \
        if (!(expr)) {           \
            assert(0 && (expr)); \
            return ret;          \
        }                        \
    } while (0)
#endif

#ifndef MM_ASSERT
#define MM_ASSERT(expr) ASSERT(expr)
#endif

#ifdef __cplusplus
}
#endif


#endif // __mm_debug_H
