#include "../include/matrix.h"

struct Matrix *mat_new(int rows, int cols) {
    struct Matrix *mat = (struct Matrix *) malloc(sizeof(struct Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (float*) calloc(cols * rows, sizeof(float));
    return mat;
}

void mat_e(struct Matrix *mat, int row, int col, float val) {
    mat->data[row * mat->rows + col] = val;
}

float mat_g(struct Matrix *mat, int row, int col) {
    return mat->data[row * mat->rows + col];
}

void mat_out(struct Matrix *mat) {
    for (int i=0; i<mat->rows * mat->cols; i++) {
        printf("%f ", mat->data[i]);
        if (0 == (i+1) % mat->cols)
            printf("\n");
    }
    printf("rows: %i, columns: %i\n", mat->rows, mat->cols);
}

void mat_delete(struct Matrix *mat) {
    free(mat->data);
    free(mat);
}

void mat_scl(struct Matrix *mat, char op, float val) {
    switch (op) {
        case '+': {
            for (int i=0; i<mat->cols * mat->rows; i++) {
                mat->data[i] += val;
            }
            break;
        }
        case '-': {
            for (int i=0; i<mat->cols * mat->rows; i++) {
                mat->data[i] -= val;
            }
            break;
        }
        case '*': {
            for (int i=0; i<mat->cols * mat->rows; i++) {
                mat->data[i] *= val;
            }
            break;
        }
        case '/': {
            if (0.0f == val)
                return;
            for (int i=0; i<mat->cols * mat->rows; i++) {
                mat->data[i] /= val;
            }
            break;
        }
        default: {
            break;
        }
    }
}

void mat_ew(struct Matrix *chmat, char op, struct Matrix *omat) {
    if (chmat->rows != omat->rows || chmat->cols != omat->cols) {
        printf("\nPANIC: element-wise operation, matrices have different dimensions\n");
        return;
    }
    switch (op) {
        case '+': {
            for (int i=0; i<chmat->cols * chmat->rows; i++) {
                chmat->data[i] += omat->data[i];
            }
            break;
        }
        case '-': {
            for (int i=0; i<chmat->cols * chmat->rows; i++) {
                chmat->data[i] -= omat->data[i];
            }
            break;
        }
        case '*': {
            for (int i=0; i<chmat->cols * chmat->rows; i++) {
                chmat->data[i] *= omat->data[i];
            }
            break;
        }
        case '/': {
            for (int i=0; i<chmat->cols * chmat->rows; i++) {
                if (0.0f == omat->data[i])
                    continue;
                chmat->data[i] /= omat->data[i];
            }
            break;
        }
        default: {
            break;
        }
    }
}

// refac to !use g, e
void mat_dot(struct Matrix *chmat, struct Matrix *omat) {
    if (chmat->cols != omat->rows) {
        printf("\nPANIC: matrices cant be dotted\n");
        return;
    }
    for (int i=0; i<chmat->rows; i++) {
        for (int j=0; j<omat->cols; j++) {
            float sum = 0.0;
            for (int k=0; k<chmat->cols; k++) {
                sum += mat_g(chmat, i, k) * mat_g(omat, k, j);
            }
            mat_e(chmat, i, j, sum);
        }
    }
}

struct Matrix *mat_identity(int nSIZE) {
    struct Matrix *mat = mat_new(nSIZE, nSIZE);
    for (int i=0; i<nSIZE; i++) {
        mat->data[i * nSIZE + i] = 1.0f;
    }
    return mat;
}

struct Matrix *mat_translation(float fx, float fy, float fz) {
    struct Matrix *mat = mat_identity(4);
    mat->data[3] = fx;
    mat->data[7] = fy;
    mat->data[11] = fz;
    return mat;
}

struct Matrix *mat_scaling(float fx, float fy, float fz) {
    struct Matrix *mat = mat_identity(4);
    mat->data[0] = fx;
    mat->data[5] = fy;
    mat->data[10] = fz;
    return mat;
}

struct Matrix *mat_shearing(float fxy, float fxz, float fyx, float fyz, float fzx, float fzy) {
    struct Matrix *mat = mat_identity(4);
    mat->data[1] = fxy;
    mat->data[2] = fxz;
    mat->data[4] = fyx;
    mat->data[6] = fyz;
    mat->data[8] = fzx;
    mat->data[9] = fzy;
    return mat;
}

struct Matrix *mat_rx(float r) {
    struct Matrix *mat = mat_identity(4);
    float cosine = cosf(r), sine = sinf(r);
    mat->data[5]  = cosine;
    mat->data[6]  =  -sine;
    mat->data[9]  =   sine;
    mat->data[10] = cosine;
    return mat;
}

struct Matrix *mat_ry(float r) {
    struct Matrix *mat = mat_identity(4);
    float cosine = cosf(r), sine = sinf(r);
    mat->data[0]  = cosine;
    mat->data[2]  =   sine;
    mat->data[8]  =  -sine;
    mat->data[10] = cosine;
    return mat;
}

struct Matrix *mat_rz(float r) {
    struct Matrix *mat = mat_identity(4);
    float cosine = cosf(r), sine = sinf(r);
    mat->data[0] = cosine;
    mat->data[1] =  -sine;
    mat->data[4] =   sine;
    mat->data[5] = cosine;
    return mat;
}

