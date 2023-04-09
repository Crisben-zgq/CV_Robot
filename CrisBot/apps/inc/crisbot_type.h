#ifndef __CRISBOT_TYPE_H__
#define __CRISBOT_TYPE_H__

#ifdef __KERNEL__

#include <linux/types.h>
#else

#include <stdint.h>
#endif

#include <pthread.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef enum {
    CRISBOT_FALSE = 0,
    CRISBOT_TRUE  = 1,
} CRISBOT_BOOL;

typedef void* 					handle;
typedef unsigned char           CRISBOT_UCHAR;
typedef unsigned char           CRISBOT_U8;
typedef unsigned short          CRISBOT_U16;
typedef unsigned int            CRISBOT_U32;
typedef unsigned long           CRISBOT_UL;
typedef CRISBOT_UL              CRISBOT_ULONG;
typedef uintptr_t               CRISBOT_UINTPTR_T;
typedef char                    CRISBOT_CHAR;
typedef signed char             CRISBOT_S8;
typedef short                   CRISBOT_S16;
typedef int                     CRISBOT_S32;
typedef long                    CRISBOT_SL;
typedef float                   CRISBOT_FLOAT;
typedef double                  CRISBOT_DOUBLE;

typedef unsigned char           crisbot_uchar;
typedef unsigned char           crisbot_u8;
typedef unsigned short          crisbot_u16;
typedef unsigned int            crisbot_u32;
typedef unsigned long           crisbot_ulong;
typedef char                    crisbot_char;
typedef signed char             crisbot_s8;
typedef short                   crisbot_s16;
typedef int                     crisbot_s32;
typedef long                    crisbot_slong;
typedef float                   crisbot_float;
typedef double                  crisbot_double;
typedef void                    crisbot_void;
#ifndef _M_IX86
    typedef unsigned long long  crisbot_u64;
    typedef long long           crisbot_s64;
#else
    typedef unsigned __int64    crisbot_u64;
    typedef __int64             crisbot_s64;
#endif

typedef unsigned long           crisbot_size_t;
typedef unsigned long           crisbot_length_t;
typedef crisbot_u32             crisbot_handle;
typedef CRISBOT_BOOL            crisbot_bool;
typedef CRISBOT_UINTPTR_T       crisbot_uintptr_t;
typedef unsigned long int       crisbot_phys_addr_t;

#ifndef NULL
    #define NULL                0L
#endif
#define CL_NULL                 0L
#define CL_SUCCESS              0
#define CL_FAILURE              (-1)
#define CL_VOID                 void
#define CL_UNUSED(x)            ((x) = (x))

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __CL_TYPE_H__ */