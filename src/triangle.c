#include "triangle.h"
#include <stdlib.h>

#ifdef SYS_64
// (64-bit) Helper to unpack 3 shorts from an int
__attribute__((nonnull(2, 3))) static inline void unpack_vertex(unsigned long long int packed, float* loc, float* out)
{
    // Assuming the packed format is: [z (short)][y (short)][x (short)]
    out[0] = (float)(((packed >> 0) & 0xFFFF) + loc[0]);
    out[1] = (float)(((packed >> 16) & 0xFFFF) + loc[1]);
    out[2] = (float)(((packed >> 32) & 0xFFFF) + loc[2]); // On 64-bit, this works — but not on 32-bit systems!
}

#elif SYS_32

// (32-bit) Helper to unpack 3 shorts from an int
__attribute__((nonnull(2, 3))) static inline void unpack_vertex(int packed, float* loc, float* out)
{
    // Assuming packed as 3 shorts inside int:
    out[0] = (float)(((packed >>  0) & 0xFF) + loc[0]);
    out[1] = (float)(((packed >>  8) & 0xFF) + loc[1]);
    out[2] = (float)(((packed >> 16) & 0xFF) + loc[2]);
}

#endif

// Extract RGB from packed color
__attribute__((nonnull(2, 3, 4))) static inline void unpack_color(int color, unsigned char* r, unsigned char* g, unsigned char* b)
{
    *r = (color >> 24) & 0xFF;
    *g = (color >> 16) & 0xFF;
    *b = (color >> 8) & 0xFF;
}

__attribute__((nonnull(1))) RenderTriangle* toRender(Triangle* tri)
{
    RenderTriangle* renderTri = (RenderTriangle*)malloc(sizeof(RenderTriangle));
    if (!renderTri) return NULL;

    for (int i = 0; i < 3; ++i)
        unpack_vertex(tri->vertices[i], tri->loc, renderTri->verticies[i]);

    unpack_color(tri->color, &renderTri->red, &renderTri->green, &renderTri->blue);

    return renderTri;
}

__attribute__((nonnull(1))) Triangle* toTriangle(RenderTriangle* tri)
{
    Triangle* compactTri = (Triangle*)malloc(sizeof(Triangle));
    if (!compactTri) return NULL;

    // Set loc[3] to the base of the first vertex
    compactTri->loc[0] = tri->verticies[0][0];
    compactTri->loc[1] = tri->verticies[0][1];
    compactTri->loc[2] = tri->verticies[0][2];

#ifdef SYS_64
    for (int i = 0; i < 3; ++i)
    {
        short x = (short)(tri->verticies[i][0] - compactTri->loc[0]);
        short y = (short)(tri->verticies[i][1] - compactTri->loc[1]);
        short z = (short)(tri->verticies[i][2] - compactTri->loc[2]);

        unsigned long long packed = 0;
        packed |= ((unsigned long long)(x & 0xFFFF)) << 0;
        packed |= ((unsigned long long)(y & 0xFFFF)) << 16;
        packed |= ((unsigned long long)(z & 0xFFFF)) << 32;

        compactTri->vertices[i] = (int)packed; // Truncate to 32-bit (assumes small deltas)
    }

#elif SYS_32
    for (int i = 0; i < 3; ++i) {
        unsigned char x = (unsigned char)(tri->verticies[i][0] - compactTri->loc[0]);
        unsigned char y = (unsigned char)(tri->verticies[i][1] - compactTri->loc[1]);
        unsigned char z = (unsigned char)(tri->verticies[i][2] - compactTri->loc[2]);

        int packed = 0;
        packed |= ((x & 0xFF) << 0);
        packed |= ((y & 0xFF) << 8);
        packed |= ((z & 0xFF) << 16);

        compactTri->vertices[i] = packed;
    }
#endif

    // Pack RGB into color
    compactTri->color = ((tri->red & 0xFF) << 24) |
                        ((tri->green & 0xFF) << 16) |
                        ((tri->blue & 0xFF) << 8) |
                        ((tri->alpha & 0xFF) << 0);

    return compactTri;
}
