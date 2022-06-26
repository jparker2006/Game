#include "utility.h"

float fmodf(float a, float b) {
    float mod;
    if (a < 0) mod = -a;
    else mod =  a;
    if (b < 0) b = -b;
    while (mod >= b) mod = mod - b;
    if (a < 0) return -mod;
    return mod;
}
