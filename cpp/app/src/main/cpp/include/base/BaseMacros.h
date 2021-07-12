/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: header file of base macros
 */
#ifndef BASE_MACROS_H
#define BASE_MACROS_H
#include <cassert>

#define DISALLOW_COPY(TypeName) TypeName(const TypeName &) = delete
#define DISALLOW_ASSIGN(TypeName) TypeName &operator = (const TypeName &) = delete
#define DISALLOW_MOVE(TypeName) TypeName(const TypeName &&) = delete
#define DISALLOW_MOVE_ASSIGN(TypeName) TypeName &operator = (const TypeName &&) = delete;

#if !defined(DISALLOW_COPY_AND_ASSIGN)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    DISALLOW_COPY(TypeName);               \
    DISALLOW_ASSIGN(TypeName)
#endif

#define DISALLOW_MOVE_AND_ASSIGN(TypeName) \
    DISALLOW_MOVE(TypeName);               \
    DISALLOW_MOVE_ASSIGN(TypeName);

#define MM_RELEASE_ARRAY(_p) \
    do {                     \
        if (_p) {            \
            delete[](_p);    \
            (_p) = nullptr;  \
        }                    \
    } while (0)

#define MM_BOOL_EXPR(_expr)       \
    ({                            \
        int _r = (_expr) ? 1 : 0; \
        _r;                       \
    })

#define MM_LIKELY(_expr) __builtin_expect(MM_BOOL_EXPR(_expr), 1)
#define MM_UNLIKELY(_expr) __builtin_expect(MM_BOOL_EXPR(_expr), 0)

#ifndef MM_ASSERT
#define MM_ASSERT(expr)          \
    do {                         \
        if (!(expr)) {           \
            assert(0 && (expr)); \
        }                        \
    } while (0)
#endif

#endif // BASE_MACROS_H_
