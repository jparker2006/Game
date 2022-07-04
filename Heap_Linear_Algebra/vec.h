#ifndef VEC_H
#define VEC_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Vector {
    int length, capacity;
    float *data;
};

void vector_new(struct Vector *vec);
void vector_rpush(struct Vector *vec, float n);
float vector_rpop(struct Vector *vec);
void vector_print(struct Vector *vec);
void vector_free(struct Vector *vec);

#endif // VEC_H
