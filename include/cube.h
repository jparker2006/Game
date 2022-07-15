#ifndef CUBE_H
#define CUBE_H

#include "../include/utility.h"

struct Cube {
    float x, y, z;
    unsigned int id;
};

static unsigned int id = 1;

#define C_RED   1.0f, 0.0f, 0.0f, 1.0f
#define C_GREEN 0.0f, 1.0f, 0.0f, 1.0f

struct Cube* cube_new(float xOff, float yOff, float zOff);
float* cadd_vertices(struct Cube** vCubes, float *vertices, int nCUBES);

#endif // CUBE_H
