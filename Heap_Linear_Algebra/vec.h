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

struct Vector *vec_new();
void vec_rpush(struct Vector *vec, float n);
float vec_rpop(struct Vector *vec);
void vec_out(struct Vector *vec);
void vec_delete(struct Vector *vec);
void vec_scl(struct Vector *vec, char op, float val);
void vec_ew(struct Vector *chvec, char op, struct Vector *ovec);
void vec_cnstr(struct Vector *vec);
void vec_cross(struct Vector *vec, struct Vector *ovec);
// maybe add mag & norm

#endif // VEC_H
