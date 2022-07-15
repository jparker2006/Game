#include "../include/cube.h"

struct Cube* cube_new(float xOff, float yOff, float zOff) {
    struct Cube *self = (struct Cube*) malloc(sizeof(struct Cube));
    self->x = xOff;
    self->y = yOff;
    self->z = zOff;
    self->id = id++;
    return self;
}

float* cadd_vertices(struct Cube** C, float *v, int nCUBES) { // C is all cubes
    int nvertices = 8, nposvec = 3, ncolvec = 4;
    size_t nVertices = (sizeof(float) * nvertices * nposvec + sizeof(float) * nvertices * ncolvec) * nCUBES;
    v = (float*) malloc(nVertices);
    size_t color_start = nvertices * nposvec * nCUBES;
    float BS = 0.04f; // block_size
    float C_BLUE[] = { 0.0f, 0.0f, 1.0f, 1.0f }; // have all cubes be blue for now
    for (int i=0; i<nCUBES; i++) {
        int x = i + 1; // adjusted indice
        v[0 * x]  =  BS + C[i]->x; v[1 * x]  =  BS + C[i]->y; v[2 * x]  =  BS + C[i]->z; // 0 (+, +, +)
        v[3 * x]  =  BS + C[i]->x; v[4 * x]  = -BS + C[i]->y; v[5 * x]  =  BS + C[i]->z; // 1 (+, -, +)
        v[6 * x]  = -BS + C[i]->x; v[7 * x]  = -BS + C[i]->y; v[8 * x]  =  BS + C[i]->z; // 2 (-, -, +)
        v[9 * x]  = -BS + C[i]->x; v[10 * x] =  BS + C[i]->y; v[11 * x] =  BS + C[i]->z; // 3 (-, +, +)
        v[12 * x] =  BS + C[i]->x; v[13 * x] =  BS + C[i]->y; v[14 * x] = -BS + C[i]->z; // 4 (+, +, -)
        v[15 * x] =  BS + C[i]->x; v[16 * x] = -BS + C[i]->y; v[17 * x] = -BS + C[i]->z; // 5 (+, -, -)
        v[18 * x] = -BS + C[i]->x; v[19 * x] = -BS + C[i]->y; v[20 * x] = -BS + C[i]->z; // 6 (-, -, -)
        v[21 * x] = -BS + C[i]->x; v[22 * x] =  BS + C[i]->y; v[23 * x] = -BS + C[i]->z; // 7 (-, +, -)
        for (int j=0; j<32; j++) {
            v[color_start + j * (i+1)] = C_BLUE[j % 4];
        }
    }

    for (int i=0; i<color_start; i++) {
        for (int j=0; j<3; j++) {
            printf("%f, ", v[i]);
        }
        printf("\n");
    }

    return v;
}
