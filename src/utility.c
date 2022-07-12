#include "../include/utility.h"

float fmodf(float a, float b) {
    float mod;
    if (a < 0) mod = -a;
    else mod =  a;
    if (b < 0) b = -b;
    while (mod >= b) mod = mod - b;
    if (a < 0) return -mod;
    return mod;
}

char* LoadFile(const char *source) {
    char *buffer = 0;
    long length = 0;
    FILE *s = fopen (source, "r");
    if (s) {
        fseek (s, 0, SEEK_END);
        length = ftell (s);
        fseek (s, 0, SEEK_SET);
        buffer = (char*) malloc (length);
        buffer[length-1] = '\0';
        if (buffer) {
            fread (buffer, 1, length, s);
        }
        fclose (s);
    }
    return buffer;
}

float deg_to_radians(float fDeg) {
    return fDeg * (TAU / 360.0f);
}

float frustumScale(float fFOVDeg) {
    return 1.0f / tan(deg_to_radians(fFOVDeg) / 2.0f);
}
