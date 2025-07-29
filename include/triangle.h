#ifndef __TRIANGLES_H__
#define __TRIANGLES_H__

#include "defs.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    // Use int instead of float, and use it to put in 3 shorts in one type
#ifdef SYS_64
    unsigned long long int vertices[3];
#elif defined(SYS_32)
    unsigned int vertices[3];
#endif
    float loc[3];
    int color; // RGBA is exactly 32-bit
} Triangle;

typedef struct
{
    float verticies[3][3];
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
} RenderTriangle;

#ifdef SYS_64
static inline __attribute__((nonnull(2, 3))) void unpack_vertex(unsigned long long int packed, float* loc, float* out);
#elif defined(SYS_32)
static inline __attribute__((nonnull(2, 3))) void unpack_vertex(int packed, float* loc, float* out);
#endif
static inline __attribute__((nonnull(2, 3, 4))) void unpack_color(int color, unsigned char* r, unsigned char* g, unsigned char* b);

Triangle*       __attribute__((nonnull(1))) toTriangle(RenderTriangle* tri);
RenderTriangle* __attribute__((nonnull(1))) toRender(Triangle* tri);

#ifdef __cplusplus
}
#endif

#endif