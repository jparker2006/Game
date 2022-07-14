#ifndef CUBE_H
#define CUBE_H

#include "../include/utility.h"

struct Cube {
    float xOff, yOff, zOff;
};

#define C_RED   1.0f, 0.0f, 0.0f, 1.0f
#define C_GREEN 0.0f, 1.0f, 0.0f, 1.0f
// float C_BLUE[] = { 0.0f, 0.0f, 1.0f, 1.0f };

struct Cube* cube_new(float xOff, float yOff, float zOff);
float* cube_vertices();

#endif // CUBE_H
