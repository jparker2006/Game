#include "vec.h"

void vector_new(struct Vector *vec) {
    vec->length = 0;
    vec->capacity = 1;
    vec->data = malloc(sizeof(float) * vec->capacity);
    memset(vec->data, 0, sizeof (float) * vec->capacity);
}

void vector_rpush(struct Vector *vec, float n) {
    vec->data[vec->length++] = n;
    if (vec->length == vec->capacity) {
        vec->capacity *= 2;
        vec->data = (float *) realloc(vec->data, sizeof(float) * vec->capacity);
    }
}

float vector_rpop(struct Vector *vec) {
    float nTemp = vec->data[--vec->length];
    vec->data[vec->length] = 0;
    if (vec->length == (int)vec->capacity / 4) {
        vec->capacity /= 2;
        vec->data = (float *) realloc(vec->data, sizeof(float) * vec->capacity);
    }
    return nTemp;
}

void vector_print(struct Vector *vec) {
    for (int i=0; i<vec->length; i++) {
        printf("%f\n", vec->data[i]);
    }
    printf("length: %i\ncapacity: %i\n", vec->length, vec->capacity);
}

void vector_free(struct Vector *vec) {
    free(vec->data);
    free(vec);
}
