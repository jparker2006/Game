#ifndef MAT_H
#define MAT_H

#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    int rows, cols;
    float **data;
};

struct Matrix *mat_new(int rows, int cols);
void mat_out(struct Matrix *mat);
void mat_delete(struct Matrix *mat);
void mat_scl(struct Matrix *mat, char op, float val);
void mat_ew(struct Matrix *chmat, char op, struct Matrix *omat);
void mat_dot(struct Matrix *chmat, struct Matrix *omat);

#endif // MAT_H
