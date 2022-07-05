#include "matrix.h"

struct Matrix *mat_new(int rows, int cols) {
    struct Matrix *mat = (struct Matrix *) malloc(sizeof(struct Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (float**) malloc(cols * sizeof(float *));
    for (int i=0; i<rows; i++) {
        mat->data[i] = (float*) calloc(cols, sizeof(float));
    }
    return mat;
}

void mat_out(struct Matrix *mat) {
    for (int i=0; i<mat->rows; i++) {
        for (int j=0; j<mat->cols; j++) {
            printf("%f ", mat->data[i][j]);
        }
        printf("\n");
    }
    printf("rows: %i, columns: %i\n", mat->rows, mat->cols);
}

void mat_delete(struct Matrix *mat) {
    for (int i=0; i<mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

void mat_scl(struct Matrix *mat, char op, float val) {
    switch (op) {
        case '+': {
            for (int i=0; i<mat->rows; i++) {
                for (int j=0; j<mat->cols; j++) {
                    mat->data[i][j] += val;
                }
            }
            break;
        }
        case '-': {
            for (int i=0; i<mat->rows; i++) {
                for (int j=0; j<mat->cols; j++) {
                    mat->data[i][j] -= val;
                }
            }
            break;
        }
        case '*': {
            for (int i=0; i<mat->rows; i++) {
                for (int j=0; j<mat->cols; j++) {
                    mat->data[i][j] *= val;
                }
            }
            break;
        }
        case '/': {
            if (0.0f == val)
                break;
            for (int i=0; i<mat->rows; i++) {
                for (int j=0; j<mat->cols; j++) {
                    mat->data[i][j] /= val;
                }
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
            for (int i=0; i<chmat->rows; i++) {
                for (int j=0; j<chmat->cols; j++) {
                    chmat->data[i][j] += omat->data[i][j];
                }
            }
            break;
        }
        case '-': {
            for (int i=0; i<chmat->rows; i++) {
                for (int j=0; j<chmat->cols; j++) {
                    chmat->data[i][j] -= omat->data[i][j];
                }
            }
            break;
        }
        case '*': {
            for (int i=0; i<chmat->rows; i++) {
                for (int j=0; j<chmat->cols; j++) {
                    chmat->data[i][j] *= omat->data[i][j];
                }
            }
            break;
        }
        case '/': {
            for (int i=0; i<chmat->rows; i++) {
                for (int j=0; j<chmat->cols; j++) {
                    if (0.0f == omat->data[i][j])
                        continue;
                    chmat->data[i][j] /= omat->data[i][j];
                }
            }
            break;
        }
        default: {
            break;
        }
    }
}

void mat_dot(struct Matrix *chmat, struct Matrix *omat) {
    if (chmat->cols != omat->rows) {
        printf("\nPANIC: matrices cant be dotted\n");
        return;
    }
    for (int i=0; i<chmat->rows; i++) {
        for (int j=0; j<omat->cols; j++) {
            float sum = 0.0;
            for (int k=0; k<chmat->cols; k++) {
                sum += chmat->data[i][k] * omat->data[k][j];
            }
            chmat->data[i][j] = sum;
        }
    }
}
