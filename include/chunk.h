#ifndef __CHUCK_H__
#define __CHUNK_H__

#include "defs.h"
#include "triangle.h"

typedef struct
{
    Triangle** triangles;
} Chunk;

#endif