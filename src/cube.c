#include "../include/cube.h"

struct Cube* cube_new(float xOff, float yOff, float zOff) {
    struct Cube *self = (struct Cube*) malloc(sizeof(struct Cube));
    self->xOff = xOff;
    self->yOff = yOff;
    self->zOff = zOff;
    return self;
}

float* cube_vertices() {
    int nvertices = 8, nposvec = 3, ncolvec = 4;
    float* v = // standard cube vertices
        (float*) malloc(sizeof(float) * nvertices * nposvec +
        sizeof(float) * nvertices * ncolvec);
    float BS = 0.04f; // block_size
    v[0]  =  BS; v[1]  =  BS; v[2]  =  BS; // 0
    v[3]  =  BS; v[4]  = -BS; v[5]  =  BS; // 1
    v[6]  = -BS; v[7]  = -BS; v[8]  =  BS; // 2
    v[9]  = -BS; v[10] =  BS; v[11] =  BS; // 3
    v[12] =  BS; v[13] =  BS; v[14] = -BS; // 4
    v[15] =  BS; v[16] = -BS; v[17] = -BS; // 5
    v[18] = -BS; v[19] = -BS; v[20] = -BS; // 6
    v[21] = -BS; v[22] =  BS; v[23] = -BS; // 7
    float C_BLUE[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    for (int i=0; i<32; i++) {
        v[24 + i] = C_BLUE[i % 4];
    }
    return v;
}
