#ifndef __CHUCK_H__
#define __CHUNK_H__

#include "defs.h"
#include "triangle.h"

typedef enum
{
    HIGH_DETAIL,
    MEDIUM_DETAIL,
    LOW_DETAIL,
    VERYLOW_DETAIL
} DetailMode;

typedef struct
{
    Triangle** triangles;
    DetailMode* detail;
    int num_triangles;
} Chunk;

#endif