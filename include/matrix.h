#ifndef MAT_H
#define MAT_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Matrix {
    int rows, cols;
    float *data;
};

struct Matrix *mat_new(int rows, int cols);
void mat_e(struct Matrix *mat, int row, int col, float val);
float mat_g(struct Matrix *mat, int row, int col);
void mat_out(struct Matrix *mat);
void mat_delete(struct Matrix *mat);
void mat_scl(struct Matrix *mat, char op, float val);
void mat_ew(struct Matrix *chmat, char op, struct Matrix *omat);
void mat_dot(struct Matrix *chmat, struct Matrix *omat);
// utility matrices
struct Matrix *mat_identity(int nSIZE);
// assume 4x4 matrice sizes,,,reason: library usage is for 3d graphics
struct Matrix *mat_translation(float fx, float fy, float fz);
struct Matrix *mat_scaling(float fx, float fy, float fz);
struct Matrix *mat_shearing(float fxy, float fxz, float fyx, float fyz, float fzx, float fzy);
// rotation matrices
struct Matrix *mat_rx(float r);
struct Matrix *mat_ry(float r);
struct Matrix *mat_rz(float r);

#endif // MAT_H
