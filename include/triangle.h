#ifndef __TRIANGLES_H__
#define __TRIANGLES_H__

#include "defs.h"

typedef struct
{
    // float[3][3] uses more memory than float[9]
    // Also, float is a lot more memory efficient than double
    float vertices[9];
    int color; // RGBA is exactly 32-bit
} Triangle __PACKED;

#endif