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

struct Vector *vec_new(int SIZE_DEF);
void vec_rpush(struct Vector *vec, float n);
void vec_lpush(struct Vector *vec, float n);
float vec_rpop(struct Vector *vec);
float vec_lpop(struct Vector *vec);
void vec_out(struct Vector *vec);
void vec_delete(struct Vector *vec);
void vec_scl(struct Vector *vec, char op, float val);
void vec_ew(struct Vector *chvec, char op, struct Vector *ovec);
void vec_cnstr(struct Vector *vec);
void vec_cross(struct Vector *vec, struct Vector *ovec);
float vec_mag(struct Vector *vec);
void vec_normal(struct Vector *vec);
void vec_sizeup(struct Vector *vec, int SIZE);

#endif // VEC_H
