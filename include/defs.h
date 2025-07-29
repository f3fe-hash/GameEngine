#ifndef __DEFS_H__
#define __DEFS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define __PACKED __attribute__((packed))

#if defined(__x86_64__) || defined(_M_X64)
#   define SYS_64
#elif defined(__i386__) || defined(_M_IX86)
#   define SYS_32
#else
#   warning "Running system on unknown CPU type. Defaulting to 32-bit."
#   define SYS_32
#endif

#ifdef __cplusplus
}
#endif

#endif