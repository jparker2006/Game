#ifndef UTILITY_H
#define UTILITY_H

#define PI  3.14159265
#define TAU 6.28318530

// c headers
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// opengl headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float fmodf(float a, float b);
char* LoadFile(const char *source);
float deg_to_radians(float fDeg);
float frustumScale(float fFOVDeg);

#endif // UTILITY_H
