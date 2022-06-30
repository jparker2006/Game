#include "../include/utility.h"

float fmodf(float a, float b) {
    float mod;
    if (a < 0) mod = -a;
    else mod = a;
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

int random_number(int upper, int lower) {
    return (rand() % (upper - lower + 1)) + lower;
}

void show_farray(float *array, unsigned long size) {
    int length = size / sizeof(float);
    for (int i=0; i<length; i++) {
        printf("%f, ", array[i]);
    }
    printf("]\n");
}
