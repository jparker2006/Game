#include "vector.h"

struct Vector *vec_new(int SIZE_DEF) {
    struct Vector *vec = (struct Vector *) malloc(sizeof(struct Vector));
    vec->length = 0;
    vec->capacity = 1;
    vec->data = (float*) calloc(vec->capacity, sizeof(float));
    if (SIZE_DEF > 0)
        vec_sizeup(vec, SIZE_DEF);
    return vec;
}

void vec_rpush(struct Vector *vec, float n) {
    vec->data[vec->length++] = n;
    if (vec->length >= vec->capacity) {
        vec->capacity *= 2;
        vec->data = (float *) realloc(vec->data, sizeof(float) * vec->capacity);
    }
}

void vec_lpush(struct Vector *vec, float n) {
    if (++vec->length >= vec->capacity) {
        vec->capacity *= 2;
        vec->data = (float *) realloc(vec->data, sizeof(float) * vec->capacity);
    }
    for (int i=vec->length; i>=0; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[0] = n;
}

float vec_rpop(struct Vector *vec) {
    float fDeleted = vec->data[--vec->length];
    vec->data[vec->length] = 0.0f;
    if (vec->length == (int)(vec->capacity / 4)) {
        vec->capacity /= 2;
        vec->data = (float *) realloc(vec->data, sizeof(float) * vec->capacity);
    }
    return fDeleted;
}

float vec_lpop(struct Vector *vec) {
    float fDeleted = vec->data[0];
    vec->length--;
    for (int i=0; i<vec->length; i++) {
        vec->data[i] = vec->data[i + 1];
    }
    return fDeleted;
}

void vec_out(struct Vector *vec) {
    for (int i=0; i<vec->length; i++) {
        printf("%f\n", vec->data[i]);
    }
    printf("length: %i\ncapacity: %i\n", vec->length, vec->capacity);
}

void vec_delete(struct Vector *vec) {
    free(vec->data);
    free(vec);
}

void vec_scl(struct Vector *vec, char op, float val) {
    switch (op) {
        case '+': {
            for (int i=0; i<vec->length; i++) {
                vec->data[i] += val;
            }
            break;
        }
        case '-': {
            for (int i=0; i<vec->length; i++) {
                vec->data[i] -= val;
            }
            break;
        }
        case '*': {
            for (int i=0; i<vec->length; i++) {
                vec->data[i] *= val;
            }
            break;
        }
        case '/': {
            if (0.0f == val)
                break;
            for (int i=0; i<vec->length; i++) {
                vec->data[i] /= val;
            }
            break;
        }
        default: {
            break;
        }
    }
}

void vec_ew(struct Vector *chvec, char op, struct Vector *ovec) {
    if (chvec->length != ovec->length) {
        printf("\nPANIC: element-wise operation, vectors have different length\n");
        return;
    }
    switch (op) {
        case '+': {
            for (int i=0; i<chvec->length; i++) {
                chvec->data[i] += ovec->data[i];
            }
            break;
        }
        case '-': {
            for (int i=0; i<chvec->length; i++) {
                chvec->data[i] -= ovec->data[i];
            }
            break;
        }
        case '*': {
            for (int i=0; i<chvec->length; i++) {
                chvec->data[i] *= ovec->data[i];
            }
            break;
        }
        case '/': {
            for (int i=0; i<chvec->length; i++) {
                if (0.0f == ovec->data[i])
                    continue;
                chvec->data[i] /= ovec->data[i];
            }
            break;
        }
        default: {
            break;
        }
    }
}

void vec_cnstr(struct Vector *vec) {
    vec->data = (float *) realloc(vec->data, sizeof(float) * vec->length);
    vec->capacity = vec->length;
}

void vec_cross(struct Vector *vec, struct Vector *ovec) {
    if (vec->length > 3) // 3d cross works for my use
        return;
    vec->data[0] = vec->data[1] * ovec->data[2] - vec->data[2] * ovec->data[1];
    vec->data[1] = vec->data[2] * ovec->data[0] - vec->data[0] * ovec->data[2];
    vec->data[2] = vec->data[0] * ovec->data[1] - vec->data[1] * ovec->data[0];
}

float vec_mag(struct Vector *vec) {
    if (vec->length != 4) // only for 4d graphic layouts
        return 0.0f;
    return (float)(sqrt(pow(vec->data[0], 2) + pow(vec->data[1], 2) + pow(vec->data[2], 2) + pow(vec->data[3], 2)));
}

void vec_normal(struct Vector *vec) {
    if (vec->length != 4)
        return;
    float fMag = vec_mag(vec);
    for (int i=0; i<4; i++) {
        vec->data[i] /= fMag;
    }
}

void vec_sizeup(struct Vector *vec, int SIZE) { // constrains size
    vec->data = (float *) realloc(vec->data, sizeof(float) * SIZE);
    vec->length = SIZE;
    vec->capacity = vec->length;
}
